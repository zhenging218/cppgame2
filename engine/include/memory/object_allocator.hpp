#pragma once

#include <type_traits>
#include <cstdint>
#include <new>
#include <utility>

#include "memory/memory_control_block.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {
    struct PageInfo {
        PageInfo * next;
    };

    struct MemoryBlockInfo {
        MemoryControlBlock* referenceCounter;
        MemoryBlockInfo *next;
    };

    template <typename T, std::size_t PageSize = 4096>
    class ObjectAllocator {
    public:
        static ObjectAllocator& getInstance();

    private:
        using byte_type = std::uint8_t;
        using byte_pointer_type = byte_type *;

        using object_type = T;
        using const_object_type = const T;
        using object_reference = object_type &;
        using const_object_reference = const_object_type &;
        using object_pointer = object_type *;
        using const_object_pointer = const_object_type *;

        static constexpr std::size_t OBJECT_SIZE = sizeof(object_type);

        static constexpr std::size_t PAGE_SIZE = PageSize;

        static constexpr std::size_t ALIGNMENT_SIZE = alignof(object_type);

        static constexpr std::size_t PAGE_HEADER_SIZE = sizeof(PageInfo);
        static constexpr std::size_t BLOCK_HEADER_SIZE = sizeof(MemoryBlockInfo);

        static constexpr std::size_t BLOCK_AREA_OFFSET = (ALIGNMENT_SIZE - (PAGE_HEADER_SIZE % ALIGNMENT_SIZE)) % ALIGNMENT_SIZE;
        static constexpr std::size_t DATA_AREA_OFFSET = (ALIGNMENT_SIZE - (BLOCK_HEADER_SIZE % ALIGNMENT_SIZE)) % ALIGNMENT_SIZE;

        static constexpr std::size_t BLOCK_SIZE = BLOCK_HEADER_SIZE + DATA_AREA_OFFSET + OBJECT_SIZE;

        static constexpr std::size_t PAGE_BLOCK_COUNT = (PAGE_SIZE - PAGE_HEADER_SIZE - BLOCK_AREA_OFFSET) / BLOCK_SIZE;

        static_assert(PAGE_BLOCK_COUNT > 0, "page size is too small to hold any objects");

        std::size_t totalPages;
        std::size_t allocated;
        std::size_t available;

        PageInfo * pages;
        MemoryBlockInfo * freeList;

        static void deallocatePolymorphicObject(void* data) {
            auto& instance = getInstance();
            MemoryBlockInfo* block = reinterpret_cast<MemoryBlockInfo*>(reinterpret_cast<byte_pointer_type>(data) - DATA_AREA_OFFSET - BLOCK_HEADER_SIZE);
            block->referenceCounter->active = false;
            object_pointer target = reinterpret_cast<object_pointer>(data);
            target->~object_type();
            block->next = instance.freeList;
            instance.freeList = block;
            instance.allocated--;
            instance.available++;
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
                curr->referenceCounter = new MemoryControlBlock(&deallocatePolymorphicObject);
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
                    }
                    delete curr->referenceCounter;
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

        ObjectAllocator() : totalPages(0), allocated(0), available(0), pages(nullptr), freeList(nullptr)
        {}

        ObjectAllocator(ObjectAllocator const &) = delete;
        ObjectAllocator &operator=(ObjectAllocator const &) = delete;
    public:
        ~ObjectAllocator() {
            while (pages != nullptr) {
                PageInfo* toFree = pages;
                pages = pages->next;
                destroyBlocks(toFree);
                std::free(toFree);
            }
        }

        template <typename U, typename = typename std::enable_if<std::is_base_of<T, U>::value>::type>
        void destroy(U *object) {
            MemoryBlockInfo * block = reinterpret_cast<MemoryBlockInfo*>(reinterpret_cast<byte_pointer_type>(object) - DATA_AREA_OFFSET - BLOCK_HEADER_SIZE);
            (block->referenceCounter->deallocator)(reinterpret_cast<void*>(object));
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

    template <typename T, std::size_t PageSize>
    ObjectAllocator<T, PageSize>& ObjectAllocator<T, PageSize>::getInstance() {
        static ObjectAllocator instance;
        return instance;
    }
}