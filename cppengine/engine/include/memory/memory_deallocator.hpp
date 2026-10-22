#ifndef MEMORY_DEALLOCATOR_HPP
#define MEMORY_DEALLOCATOR_HPP
#include "memory_control_block.hpp"

namespace cppengine
{
    struct MemoryDeallocator
    {
        void *context;
        void (*deallocator)(void *, void *, MemoryControlBlock::DeallocationPhase);

        constexpr MemoryDeallocator(void *context_, void (*deallocator_)(void *, void *, MemoryControlBlock::DeallocationPhase)) : context(context_), deallocator(deallocator_) {}
        constexpr MemoryDeallocator(void (*deallocator_)(void *, void *, MemoryControlBlock::DeallocationPhase)) : context(nullptr), deallocator(deallocator_) {}

        void operator()(void * object, MemoryControlBlock::DeallocationPhase phase) const;
    };
}

#endif