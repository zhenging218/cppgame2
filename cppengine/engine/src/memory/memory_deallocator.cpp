#include "engine.hpp"

namespace cppengine
{
    void MemoryDeallocator::operator()(void* object, DeallocationPhase phase) const
    {
        deallocator(context, object, phase);
    }
}
