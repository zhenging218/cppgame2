#ifndef MEMORY_CONTROL_BLOCK_HPP
#define MEMORY_CONTROL_BLOCK_HPP

#include "memory_deallocator.hpp"

namespace cppengine {
    struct MemoryControlBlock {
    private:
        using deallocator_type = MemoryDeallocator;

        template<typename T, std::size_t>
        friend class ObjectAllocator;

        bool active;
        std::size_t acquireCount;
        std::size_t weakAcquireCount;
        deallocator_type deallocator;

        MemoryControlBlock(deallocator_type deallocator_);

    public:
        std::size_t getAcquireCount() const;
        std::size_t getWeakAcquireCount() const;
        deallocator_type getDeallocator() const;

        void acquire();
        void release();

        void weakAcquire();
        void weakRelease();
    };
}

#endif