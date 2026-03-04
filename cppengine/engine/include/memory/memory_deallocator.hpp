#ifndef MEMORY_DEALLOCATOR_HPP
#define MEMORY_DEALLOCATOR_HPP

namespace cppengine
{
    struct MemoryDeallocator
    {
        void *context;
        void (*deallocator)(void *, void *);

        constexpr MemoryDeallocator(void *context_, void (*deallocator_)(void *, void *)) : context(context_), deallocator(deallocator_) {}
        constexpr MemoryDeallocator(void (*deallocator_)(void *, void *)) : context(nullptr), deallocator(deallocator_) {}

        void operator()(void * object) const;
    };
}

#endif