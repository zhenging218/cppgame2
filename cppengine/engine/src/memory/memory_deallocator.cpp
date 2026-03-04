#include "engine.hpp"

namespace cppengine
{
    void MemoryDeallocator::operator()(void* object) const
    {
        deallocator(context, object);
    }
}
