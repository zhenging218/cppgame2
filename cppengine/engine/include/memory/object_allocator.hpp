#ifndef OBJECT_ALLOCATOR_HPP
#define OBJECT_ALLOCATOR_HPP

#include <type_traits>
#include <cstdint>
#include <new>
#include <utility>

#include "memory/memory_control_block.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {
    template <typename T>
    class ObjectHandle;
    /*
    
    Do the following to allocate a page:
    1. Move to next address at multiple of max(alignof(pointer type), alignof(T), alignof(page header), alignof(block header)) from the top
    2. Place the page header
    3. Move to next address at multiple of max(alignof(block header), alignof(T)) from the page header
    4. Place the block header
    5. Move to next address at multiple of alignof(T) and place the object
    6. move to next address at multiple of max(alignof(block header), alignof(T)) Repeat 4,5 and 6 until no. of blocks has been built
    
    I will allocate total page size + max(alignof(pointer type), alignof(page header), alignof(block header), alignof(T)) of memory for a given page.

    The next address is computed as such:
    A = max(alignof(set of sub objects the header controls inclusive of  descents of the sub objects))
    next address = current address + ( (A  - current address % A) % A).

    The 4 roundups I think I need are:
    Ar - to get to the page from the raw top of the memory
    Ap - to get to the block area from the end of the page header
    Ab - to get to the object area from the end of the block header
    At - to get to the end of the block

    The alignment portions of the roundup are as follows:
    For Ar = max(alignof(pointer type), alignof(T), alignof(page header), alignof(block header))
    For Ap = max(alignof(block header), alignof(T))
    For Ab = alignof(T)
    For At = max(alignof(block header), alignof(T))

    Once allocated, for any given block, to reach the object area I do block header address + sizeof(block header) + Ab. To reach the block area of the page, I do page header address + sizeof(page header) + Ap, to reach the end of the block, I do object area address + sizeof(T) + At, to reach the page itself I do raw address + Ar. Ar is a runtime computation, while Ap, Ab and At are compile time.

    When computing the amount of blocks per page, perform the following:

    Compute the block size (with tail padding) i.e. block header + Ab + sizeof(T) + At
    1. Get the size of the top area (sizeof(page header) + Ap)
    2. Subtract (2) from the configured page size
    3. Divide (3) by (1)

    Block size is compile time computation, since it is not influenced by the address of the top of the entire memory area at runtime.
        
    */


    struct PageInfo {
        PageInfo * next;
    };

    struct MemoryBlockInfo {
        MemoryControlBlock* referenceCounter;
        MemoryBlockInfo *next;
    };

    template <typename T, std::size_t SuggestedPageSize = 4096>
    class ObjectAllocator {
    private:

        using byte_type = std::uint8_t;
        using byte_pointer_type = byte_type *;

        using object_type = T;
        using const_object_type = const T;
        using object_reference = object_type &;
        using const_object_reference = const_object_type &;
        using object_pointer = object_type *;
        using const_object_pointer = const_object_type *;

        static constexpr std::size_t getAdjustedPageSize(std::size_t minimumBlocks, std::size_t blockSize, std::size_t pageSize) {
            while (blockSize > pageSize >> minimumBlocks) {
                pageSize = pageSize << 1;
            }

            return pageSize;
        }

        static constexpr std::size_t MIN_BLOCK_COUNT_LOG_BASE_2 = 4;

        static constexpr std::size_t OBJECT_SIZE = sizeof(object_type);

        static constexpr std::size_t ALIGNMENT_SIZE = alignof(object_type);

        static constexpr std::size_t PAGE_HEADER_SIZE = sizeof(PageInfo);
        static constexpr std::size_t BLOCK_HEADER_SIZE = sizeof(MemoryBlockInfo);

        static constexpr std::size_t BLOCK_AREA_OFFSET = (ALIGNMENT_SIZE - (PAGE_HEADER_SIZE % ALIGNMENT_SIZE)) % ALIGNMENT_SIZE;
        static constexpr std::size_t DATA_AREA_OFFSET = (ALIGNMENT_SIZE - (BLOCK_HEADER_SIZE % ALIGNMENT_SIZE)) % ALIGNMENT_SIZE;

        static constexpr std::size_t BLOCK_SIZE = BLOCK_HEADER_SIZE + DATA_AREA_OFFSET + OBJECT_SIZE;

        static constexpr std::size_t PAGE_SIZE = getAdjustedPageSize(MIN_BLOCK_COUNT_LOG_BASE_2, BLOCK_SIZE, SuggestedPageSize);

        static constexpr std::size_t PAGE_BLOCK_COUNT = (PAGE_SIZE - PAGE_HEADER_SIZE - BLOCK_AREA_OFFSET) / BLOCK_SIZE;

        static_assert(PAGE_BLOCK_COUNT > 0, "page size is too small to hold any objects");

        std::size_t totalPages;
        std::size_t allocated;
        std::size_t available;

        PageInfo * pages;
        MemoryBlockInfo * freeList;

        static void deallocatePolymorphicObject(void *allocator, void* data, DeallocationPhase phase) {
            auto* instance = reinterpret_cast<ObjectAllocator*>(allocator);
            MemoryBlockInfo* block = reinterpret_cast<MemoryBlockInfo*>(reinterpret_cast<byte_pointer_type>(data) - DATA_AREA_OFFSET - BLOCK_HEADER_SIZE);
            object_pointer target = reinterpret_cast<object_pointer>(data);
            switch (phase) {
                case DeallocationPhase::DESTROY:
                    target->~object_type();
                    break;
                case DeallocationPhase::RELEASE:
                    block->referenceCounter->active = false;
                    block->next = instance->freeList;
                    instance->freeList = block;
                    instance->allocated--;
                    instance->available++;
                    break;
                default:
                    break;
            }
        }

        void initialiseBlocks(PageInfo* page) {
            void *blocks = reinterpret_cast<byte_pointer_type>(page) + PAGE_HEADER_SIZE + BLOCK_AREA_OFFSET;

            MemoryBlockInfo *first = reinterpret_cast<MemoryBlockInfo*>(blocks);
            MemoryBlockInfo *curr = first;
            MemoryBlockInfo *prev = nullptr;

            for(std::size_t i = 0; i < PAGE_BLOCK_COUNT; ++i) {
                curr->referenceCounter = nullptr;
                curr->next = nullptr;

                if(prev != nullptr) {
                    prev->next = curr;
                }

                prev = curr;
                curr = reinterpret_cast<MemoryBlockInfo*>(reinterpret_cast<byte_pointer_type>(curr) + BLOCK_SIZE);
            }

            curr = first;
            prev = nullptr;

            while (curr != nullptr) {
                curr->referenceCounter = new MemoryControlBlock({this, &deallocatePolymorphicObject});
                prev = curr;
                curr = curr->next;
            }

            if(prev != nullptr) {
                prev->next = freeList;
            }

            available += PAGE_BLOCK_COUNT;
            freeList = first;
        }

        void destroyBlocks(PageInfo* page) {
            void* blocks = reinterpret_cast<byte_pointer_type>(page) + PAGE_HEADER_SIZE + BLOCK_AREA_OFFSET;

            MemoryBlockInfo* curr = reinterpret_cast<MemoryBlockInfo*>(blocks);

            for (std::size_t i = 0; i < PAGE_BLOCK_COUNT; ++i) {

                if (curr->referenceCounter != nullptr) {
                    if (curr->referenceCounter->active) {
                        reinterpret_cast<object_pointer>(reinterpret_cast<byte_pointer_type>(curr) + BLOCK_HEADER_SIZE + DATA_AREA_OFFSET)->~T();
                        curr->referenceCounter->active = false;
                    }

                    if (curr->referenceCounter->getAcquireCount() == 0 && curr->referenceCounter->getWeakAcquireCount() == 0) {
                        delete curr->referenceCounter;
                    }
                }
                curr = reinterpret_cast<MemoryBlockInfo*>(reinterpret_cast<byte_pointer_type>(curr) + BLOCK_SIZE);
            }
        }

        void createPage() {
            PageInfo *page = reinterpret_cast<PageInfo*>(std::malloc(PAGE_SIZE));
            if(page != nullptr) {
                page->next = pages;
                pages = page;
                totalPages++;
                initialiseBlocks(page);
            } else {
                throw std::bad_alloc();
            }
        }
    public:
        ObjectAllocator() : totalPages(0), allocated(0), available(0), pages(nullptr), freeList(nullptr)
        {}

        ObjectAllocator(ObjectAllocator const &) = delete;
        ObjectAllocator &operator=(ObjectAllocator const &) = delete;

        ~ObjectAllocator() {
            while (pages != nullptr) {
                PageInfo* toFree = pages;
                pages = pages->next;
                destroyBlocks(toFree);
                std::free(toFree);
            }
        }

        template <typename ... Args>
        ObjectHandle<object_type> createHandle(Args &&... args) {
            if(freeList == nullptr) {
                createPage();
            }

            MemoryBlockInfo *block = freeList;
            byte_pointer_type data_area = reinterpret_cast<byte_pointer_type>(block) + BLOCK_HEADER_SIZE + DATA_AREA_OFFSET;

            block->referenceCounter->active = true;
            freeList = block->next;
            block->next = nullptr;

            object_pointer constructed = std::launder(new (data_area) T(std::forward<Args>(args)...));

            allocated++;
            available--;

            return ObjectHandle<T>(
                constructed, block->referenceCounter
            );
        }

        std::size_t getTotalPages() const {
            return totalPages;
        }

        std::size_t getAvailableBlockCount() const {
            return available;
        }

        std::size_t getAllocatedBlockCount() const {
            return allocated;
        }
    };

    template <typename T, std::size_t PageSize>
    class ObjectAllocator<const T, PageSize>;

    template <typename T, std::size_t PageSize>
    class ObjectAllocator<T&, PageSize>;

}

#endif