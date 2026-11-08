#ifndef REFERENCE_COUNTER_HPP
#define REFERENCE_COUNTER_HPP

#include "memory/memory_control_block.hpp"

namespace cppengine {
    class ReferenceCounter {
    private:

    protected:
        using deallocator_type = MemoryDeallocator;
        using count_getter_type = std::size_t& (*)(void*);
        using count_manipulator_type = void(*)(std::size_t&);

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

        static void destroyReferenceCounter(ReferenceCounter *counter);
    };

    class EmptyReferenceCounter : public ReferenceCounter {
    private:
        std::size_t count;
        std::size_t weakCount;

    public:
        EmptyReferenceCounter();

        void acquire() override;
        void release() override;
        void weakAcquire() override;
        void weakRelease() override;

        void* getData() const override;
        std::size_t getCount() const override;
        std::size_t getWeakCount() const override;
        deallocator_type getDeallocator() const override;

        static EmptyReferenceCounter *getEmptyReferenceCounter();
    };

    template<typename T>
    class ImmediateReferenceCounter : public ReferenceCounter {
    private:
        T* data;
        std::size_t count;
        std::size_t weakCount;
        deallocator_type deallocator;

        static void defaultDeallocator(void *, void* object, DeallocationPhase phase) {
            if (phase == DeallocationPhase::DESTROY) {
                delete reinterpret_cast<T*>(object);
            }
        }

    public:
        ImmediateReferenceCounter(T* data_, deallocator_type deallocator_)
            : data(data_), count(0), weakCount(0), deallocator(deallocator_)
        {

        }

        ImmediateReferenceCounter(T* data_) :
            ImmediateReferenceCounter(data_, deallocator_type{ .context = nullptr, .deallocator = &defaultDeallocator})
        {

        }

        void acquire() override {
            ++count;
        }

        void release() override {
            --count;
        }

        void weakAcquire() override {
            ++weakCount;
        }

        void weakRelease() override {
            --weakCount;
        }

        void* getData() const override {
            return reinterpret_cast<T*>(data);
        }

        std::size_t getCount() const override {
            return count;
        }

        std::size_t getWeakCount() const override {
            return weakCount;
        }

        deallocator_type getDeallocator() const override {
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
            : data(data_), counter(counter_) {}

        void acquire() override {
            counter->acquire();
        }

        void release() override {
            counter->release();
        }

        void weakAcquire() override {
            counter->weakAcquire();
        }

        void weakRelease() override {
            counter->weakRelease();
        }

        void* getData() const override {
            return reinterpret_cast<void *>(data);
        }

        std::size_t getCount() const override {
            return counter->getAcquireCount();
        }

        std::size_t getWeakCount() const override {
            return counter->getWeakAcquireCount();
        }

        deallocator_type getDeallocator() const override {
            return counter->getDeallocator();
        }
    };

    template <typename T>
    class UnownedTypeReference : public ReferenceCounter {
    private:
        T *data;
        std::size_t count;
        std::size_t weakCount;

    public:
        UnownedTypeReference(T &reference) : data(&reference), count(0), weakCount(0) {
        }

        void *getData() const override {
            return reinterpret_cast<T*>(data);
        }

        void acquire() override {
            ++count;
        }

        void release() override {
            --count;
        }

        void weakAcquire() override {
            ++weakCount;
        }

        void weakRelease() override {
            --weakCount;
        }

        std::size_t getCount() const override {
            return count;
        }

        std::size_t getWeakCount() const override {
            return weakCount;
        }

        deallocator_type getDeallocator() const override {
            return { .context = nullptr, .deallocator = [](void *, void *, DeallocationPhase) {} };
        }
    };
}

#endif