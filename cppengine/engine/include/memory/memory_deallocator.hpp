#ifndef MEMORY_DEALLOCATOR_HPP
#define MEMORY_DEALLOCATOR_HPP

#include "enum_deallocation_phase.hpp"

namespace cppengine
{
    struct MemoryDeallocator
    {
        void *context;
        void (*deallocator)(void *, void *, DeallocationPhase);

        constexpr MemoryDeallocator(void *context_, void (*deallocator_)(void *, void *, DeallocationPhase)) : context(context_), deallocator(deallocator_) {}
        constexpr MemoryDeallocator(void (*deallocator_)(void *, void *, DeallocationPhase)) : context(nullptr), deallocator(deallocator_) {}

        void operator()(void * object, DeallocationPhase phase) const;
    };
}

#endif