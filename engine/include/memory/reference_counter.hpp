#pragma once

struct MemoryControlBlock;

class ReferenceCounter {
private:

    void signalAcquisition() const;
    void signalDestruction() const;

protected:
    using deallocator_type = void(*)(void*);
    using count_getter_type = std::size_t& (*)(void*);
    using count_manipulator_type = void(*)(std::size_t&);

    static void incrementingAcquirer(std::size_t& count);
    static void decrementingReleaser(std::size_t& count);

public:
    ReferenceCounter();

    virtual void acquire() = 0;
    virtual void  release() = 0;

    virtual void weakAcquire() = 0;
    virtual void weakRelease() = 0;

    virtual ~ReferenceCounter();

    virtual void* getData() const = 0;
    virtual std::size_t getCount() const = 0;
    virtual std::size_t getWeakCount() const = 0;
    virtual deallocator_type getDeallocator() const = 0;
};

class EmptyReferenceCounter : public ReferenceCounter {
private:
    std::size_t count;
    std::size_t weakCount;

public:
    EmptyReferenceCounter();

    virtual void acquire() override;
    virtual void release() override;
    virtual void weakAcquire() override;
    virtual void weakRelease() override;

    virtual void* getData() const override;
    virtual std::size_t getCount() const override;
    virtual std::size_t getWeakCount() const override;
    virtual deallocator_type getDeallocator() const override;
};

template<typename T>
class ImmediateReferenceCounter : public ReferenceCounter {
private:
    T* data;
    std::size_t count;
    std::size_t weakCount;
    deallocator_type deallocator;

    static void defaultDeallocator(void* object) { delete reinterpret_cast<T*>(object); }

public:
    ImmediateReferenceCounter(T* data_, deallocator_type deallocator_)
        : ReferenceCounter(), data(data_), count(0), weakCount(0), deallocator(deallocator_)
    {

    }

    ImmediateReferenceCounter(T* data_) : 
        ImmediateReferenceCounter(data_, &defaultDeallocator)
    {

    }

    virtual void acquire() override {
        ++count;
    }

    virtual void release() override {
        --count;
    }

    virtual void weakAcquire() override {
        ++weakCount;
    }

    virtual void weakRelease() override {
        --weakCount;
    }

    virtual void* getData() const override {
        return reinterpret_cast<T*>(data);
    }

    virtual std::size_t getCount() const override {
        return count;
    }

    virtual std::size_t getWeakCount() const override {
        return weakCount;
    }

    virtual deallocator_type getDeallocator() const override {
        return deallocator;
    }
};

template <typename T>
class TypeReferenceCounter : public ReferenceCounter {
private:
    T* data;
    MemoryControlBlock* counter;
public:
    TypeReferenceCounter(T* data_, MemoryControlBlock*counter_)
        : ReferenceCounter(), data(data_), 
        counter(counter_) {}

    virtual void acquire() override {
        counter->acquire();
    }

    virtual void release() override {
        counter->release();
    }

    virtual void weakAcquire() override {
        counter->weakAcquire();
    }

    virtual void weakRelease() override {
        counter->weakRelease();
    }

    virtual void* getData() const override {
        return reinterpret_cast<T*>(data);
    }

    virtual std::size_t getCount() const override {
        return counter->getAcquireCount();
    }

    virtual std::size_t getWeakCount() const override {
        return counter->getWeakAcquireCount();
    }

    virtual deallocator_type getDeallocator() const override {
        return counter->getDeallocator();
    }
};