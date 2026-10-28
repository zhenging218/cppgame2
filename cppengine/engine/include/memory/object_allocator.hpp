#ifndef OBJECT_ALLOCATOR_HPP
#define OBJECT_ALLOCATOR_HPP

#include <new>
#include <utility>
#include <initializer_list>
#include <algorithm>
#include <functional>

#include "memory/memory_control_block.hpp"

namespace cppengine {
    template <typename T>
    class ObjectHandle;
    /*
    
    Do the following to allocate a page:
    1. Move to next address at multiple of max(alignof(pointer type), alignof(T), alignof(page header), alignof(block header)) from the top
    2. Place the page header
    3. Move to next address at multiple of max(alignof(block header), alignof(T)) from the end of the page header
    4. Place the block header
    5. Move to next address at multiple of alignof(T) and place the object
    6. move to next address at multiple of max(alignof(block header), alignof(T))
    7. Repeat 4, 5 and 6 until no. of blocks has been built
    
    I will allocate total page size +
        max(alignof(pointer type), alignof(page header),
        alignof(block header), alignof(T)) of memory for a given page.

    The next address is computed as such:
    alignment of the current section of the memory - A
    A = max(alignof(set of sub objects the header controls
        inclusive of descents of the sub objects))

    no. of bytes to pad, rounded up (roundup function) - R
    R = ((A - current address % A) % A)

    next address = current address + R.

    The 4 roundups I think I need are:
    Rr - to get to the page from the raw top of the memory
    Rp - to get to the block area from the end of the page header
    Rb - to get to the object area from the end of the block header
    Rt - to get to the end of the block

    The alignment portions of the roundup are as follows:
    For Ar = max(alignof(pointer),
        alignof(T), alignof(page header), alignof(block header))
    For Ap = max(alignof(block header), alignof(T))
    For Ab = alignof(T)
    For At = max(alignof(block header), alignof(T))

    Once allocated, for any given block, to reach the object area
        I do block header address + sizeof(block header) + Rb.
    To reach the block area of the page,
        I do page header address + sizeof(page header) + Rp,
    to reach the end of the block,
        I do object area address + sizeof(T) + Rt,
    to reach the page itself,
        I do raw address + Rr.

    Ar, Ap, Ab and At are all compile time computations
        Rr is a runtime computation, while Rp, Rb and Rt are compile time.

    actual page boundary (start of page header) is aligned correctly
        after offsetting by Rr, making (address of page header) % Ar == 0,
        which makes Rp, Rb and Rt always valid even when computed at
        compile time, so intra page alignment is always assuming
        entire memory starts at correct alignment

    The padding portions computed by the roundup is as follows:
    Rr = (Ar - top of the entire memory area % Ar) % Ar
    Rp = (Ap - page header size % Ap) % Ap
    Rb = (Ab - block header size % Ab) % Ab
    Rt = (At - (block header size + Rb + object size) % At) % At

    When computing the amount of blocks per page, perform the following:

    1. Compute the block size (with tail padding)
       i.e. block header + Rb + sizeof(T) + Rt
    2. Get the size of the top area (sizeof(page header) + Rp)
    3. Subtract (2) from the configured page size
    4. Divide (3) by (1)

    block size is compile time computation, it is not influenced by Rr,
        which is the only runtime computed padding.

    i.e. page allocation steps are as follows for page size S, object size T:

    page header size is HP
    block header size is HB
    object size is T
    block size B is HB + Rb + T + Rt

    Allocate S + Ar bytes, address of top of page at M0
    populate page header at M0 + Rr = M1
    for each block Bi, i in [0, n) from B0 = M1 + HP + Rp,
        up to Bn-1, n = (S - (HP + Rp)) / B
            populate block header at Bi
            object Ti to be placed at Bi + HB + Rb
            Bi+1 to be computed as Bi + B
            advance to Bi+1
    */

    struct MemoryBlockInfo {
        MemoryControlBlock referenceCounter;
        MemoryBlockInfo *next;
    };

    struct PageInfo {
        void * top;
        PageInfo * next;
        MemoryBlockInfo *blocks;
    };

    template <typename T, typename U>
    concept CallableType = requires(U && u, T & t) { { std::invoke(u, t) } -> std::same_as<void>; };

    template <typename T, std::size_t SuggestedPageSize = 4096>
    class ObjectAllocator {
    private:
        using byte_type = std::byte;
        using byte_pointer_type = byte_type *;

        using object_type = T;
        using const_object_type = const T;
        using object_reference_type = object_type &;
        using const_object_reference_type = const_object_type &;
        using object_pointer_type = object_type *;
        using const_object_pointer_type = const_object_type *;

        static constexpr std::size_t PAGE_HEADER_SIZE = sizeof(PageInfo);
        static constexpr std::size_t BLOCK_HEADER_SIZE = sizeof(MemoryBlockInfo);
        static constexpr std::size_t OBJECT_SIZE = sizeof(T);

        static constexpr std::size_t MEMORY_ALIGN = std::max(std::initializer_list{
            alignof(void*), alignof(PageInfo), alignof(MemoryBlockInfo), alignof(object_type)
        });
        static constexpr std::size_t PAGE_ALIGN = std::max(
            alignof(MemoryBlockInfo), alignof(object_type));
        static constexpr std::size_t BLOCK_ALIGN = alignof(T);
        static constexpr std::size_t BLOCK_TAIL_ALIGN = PAGE_ALIGN;

        static constexpr std::size_t PAGE_PADDING
            = (PAGE_ALIGN - PAGE_HEADER_SIZE % PAGE_ALIGN) % PAGE_ALIGN;
        static constexpr std::size_t BLOCK_PADDING
            = (BLOCK_ALIGN - BLOCK_HEADER_SIZE % BLOCK_ALIGN) % BLOCK_ALIGN;
        static constexpr std::size_t BLOCK_TAIL_PADDING
            = (BLOCK_TAIL_ALIGN - (BLOCK_HEADER_SIZE + BLOCK_PADDING + OBJECT_SIZE)
                % BLOCK_TAIL_ALIGN) % BLOCK_TAIL_ALIGN;

        static constexpr std::size_t BLOCK_SIZE = BLOCK_HEADER_SIZE + BLOCK_PADDING + OBJECT_SIZE + BLOCK_TAIL_PADDING;

        static constexpr std::size_t TOTAL_TO_ALLOCATE = SuggestedPageSize + MEMORY_ALIGN;
        static constexpr std::size_t TOTAL_BLOCK_COUNT = (SuggestedPageSize - (PAGE_HEADER_SIZE + PAGE_PADDING)) / BLOCK_SIZE;

        static_assert(MEMORY_ALIGN % PAGE_ALIGN == 0 && MEMORY_ALIGN % BLOCK_TAIL_ALIGN == 0,
            "allocation correction on the page is not correctly computed");
        static_assert((PAGE_HEADER_SIZE + PAGE_PADDING) % PAGE_ALIGN == 0, "blocks are not aligned correctly");
        static_assert((BLOCK_HEADER_SIZE + BLOCK_PADDING) % BLOCK_ALIGN == 0, "objects are not aligned correctly");
        static_assert(BLOCK_SIZE % BLOCK_TAIL_ALIGN == 0, "block strides are not correct");
        static_assert(SuggestedPageSize >= (PAGE_HEADER_SIZE + PAGE_PADDING) && TOTAL_BLOCK_COUNT >= 1, "Suggested page size is too small");

        static std::size_t getMemoryPadding(void * memory) noexcept {
            const auto address = reinterpret_cast<std::uintptr_t>(memory);
            return (MEMORY_ALIGN - address % MEMORY_ALIGN) % MEMORY_ALIGN;
        }

        std::size_t totalPages;
        std::size_t allocated;
        std::size_t available;

        PageInfo * pages;
        MemoryBlockInfo * freeList;

        static void deallocatePolymorphicObject(void *allocator, void* data, DeallocationPhase phase) {
            auto* instance = static_cast<ObjectAllocator*>(allocator);
            auto* block = reinterpret_cast<MemoryBlockInfo*>(
                static_cast<byte_pointer_type>(data) - BLOCK_PADDING - BLOCK_HEADER_SIZE);
            auto target = static_cast<object_pointer_type>(data);
            switch (phase) {
                case DeallocationPhase::DESTROY:
                    target->~object_type();
                    block->referenceCounter.active = false;
                    break;
                case DeallocationPhase::RELEASE:
                    block->next = instance->freeList;
                    instance->freeList = block;
                    --instance->allocated;
                    ++instance->available;
                    break;
                default:
                    break;
            }
        }

        static void destroyPage(PageInfo* page) {
            auto memory = page->top;
            auto block = page->blocks;

            for (std::size_t i = 0; i < TOTAL_BLOCK_COUNT; ++i) {
                if (block->referenceCounter.active) {
                    reinterpret_cast<object_pointer_type>(reinterpret_cast<byte_pointer_type>(block) + BLOCK_HEADER_SIZE + BLOCK_PADDING)->~object_type();
                }
                auto next = reinterpret_cast<MemoryBlockInfo *>(reinterpret_cast<byte_pointer_type>(block) + BLOCK_SIZE);
                block->~MemoryBlockInfo();
                block = next;
            }
            page->~PageInfo();
            std::free(memory);
        }

        void createPage() {
            void *memory = std::malloc(TOTAL_TO_ALLOCATE);

            if (memory == nullptr) {
                throw std::bad_alloc();
            }

            auto memoryPadding = getMemoryPadding(memory);

            auto page = reinterpret_cast<PageInfo*>(static_cast<byte_pointer_type>(memory) + memoryPadding);

            if (reinterpret_cast<std::uintptr_t>(page) % MEMORY_ALIGN != 0
                || reinterpret_cast<byte_pointer_type>(page) + SuggestedPageSize > static_cast<byte_pointer_type>(memory) + TOTAL_TO_ALLOCATE) {
                std::free(memory);
                throw std::bad_alloc();
            }

            new (page) PageInfo{ .top = memory, .next = nullptr, .blocks = reinterpret_cast<MemoryBlockInfo*>(reinterpret_cast<byte_pointer_type>(page) + PAGE_HEADER_SIZE + PAGE_PADDING) };

            auto block = page->blocks;

            for (std::size_t i = 0; i < TOTAL_BLOCK_COUNT; ++i) {
                new (block) MemoryBlockInfo{ .referenceCounter = MemoryControlBlock(MemoryDeallocator{ .context = this, .deallocator = &deallocatePolymorphicObject}), .next = nullptr };

                if (i + 1 < TOTAL_BLOCK_COUNT) {
                    auto next = reinterpret_cast<MemoryBlockInfo*>(reinterpret_cast<byte_pointer_type>(block) + BLOCK_SIZE);
                    block->next = next;
                    block = next;
                }
            }

            block->next = freeList;
            page->next = pages;

            pages = page;
            freeList = page->blocks;
            totalPages++;
            available += TOTAL_BLOCK_COUNT;
        }

    public:
        ObjectAllocator() : totalPages(0), allocated(0), available(0), pages(nullptr), freeList(nullptr)
        {}

        ObjectAllocator(ObjectAllocator const &) = delete;
        ObjectAllocator &operator=(ObjectAllocator const &) = delete;

        ~ObjectAllocator() {
            while (pages != nullptr) {
                auto next = pages->next;
                auto page = pages;
                destroyPage(page);
                pages = next;
            }
        }

        template <typename ... Args>
        ObjectHandle<object_type> createHandle(Args &&... args) {
            if (freeList == nullptr) {
                createPage();
            }

            auto result = freeList;
            auto object = new (reinterpret_cast<object_pointer_type>(reinterpret_cast<byte_pointer_type>(result) + BLOCK_HEADER_SIZE + BLOCK_PADDING)) object_type(std::forward<Args>(args)...);
            auto handle = ObjectHandle(object, &result->referenceCounter);
            result->referenceCounter.active = true;

            freeList = freeList->next;
            ++allocated;
            --available;

            return handle;
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

        template <typename U> requires CallableType<T, U>
        void visit(U &&visitor) {
            auto page = pages;

            while (page != nullptr) {
                auto block = reinterpret_cast<byte_pointer_type>(page) + PAGE_HEADER_SIZE + PAGE_PADDING;

                for (std::size_t i = 0; i < TOTAL_BLOCK_COUNT; ++i) {
                    if (reinterpret_cast<MemoryBlockInfo*>(block)->referenceCounter.active) {
                        auto object = reinterpret_cast<object_pointer_type>(block + BLOCK_HEADER_SIZE + BLOCK_PADDING);
                        std::invoke(visitor, *object);
                    }

                    block = block + BLOCK_SIZE;
                }
                page = page->next;
            }
        }

    };

    template <typename T, std::size_t PageSize>
    class ObjectAllocator<const T, PageSize>;

    template <typename T, std::size_t PageSize>
    class ObjectAllocator<T&, PageSize>;

}

#endif