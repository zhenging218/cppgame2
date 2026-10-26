#ifndef MEMORY_DEALLOCATOR_HPP
#define MEMORY_DEALLOCATOR_HPP

#include "enum_deallocation_phase.hpp"

namespace cppengine
{
    struct MemoryDeallocator
    {
        void *context;
        void (*deallocator)(void *, void *, DeallocationPhase);

        void operator()(void * object, DeallocationPhase phase) const;
    };
}

#endif