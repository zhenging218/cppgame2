#include "engine.hpp"

namespace cppengine
{
    void MemoryDeallocator::operator()(void* object, MemoryControlBlock::DeallocationPhase phase) const
    {
        deallocator(context, object, phase);
    }
}
