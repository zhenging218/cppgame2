#pragma once

struct MemoryControlBlock {
private:
    using deallocator_pointer = void (*)(void*);

    template<typename T, std::size_t>
    friend class ObjectAllocator;

    bool active;
    std::size_t acquireCount;
    std::size_t weakAcquireCount;
    deallocator_pointer deallocator;

    MemoryControlBlock(deallocator_pointer deallocator_);

public:
    std::size_t getAcquireCount() const;
    std::size_t getWeakAcquireCount() const;
    deallocator_pointer getDeallocator() const;

    void acquire();
    void release();

    void weakAcquire();
    void weakRelease();
};