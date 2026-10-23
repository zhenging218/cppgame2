#ifndef OBJECT_HANDLE_HPP
#define OBJECT_HANDLE_HPP

#include <type_traits>

#include "object_allocator.hpp"
#include "reference_counter.hpp"

namespace cppengine {
    template <typename T, typename U>
    concept ComparableObjectHandles =
        std::is_base_of<
        typename std::remove_const<T>::type,
        typename std::remove_const<U>::type
        >::value ||
        std::is_base_of<
        typename std::remove_const<U>::type,
        typename std::remove_const<T>::type
        >::value;

    template <typename T, typename U>
    concept ConvertibleObjectHandles = std::is_assignable<T*&, U*>::value &&
        !std::is_same<T, U>::value && std::is_base_of<typename std::remove_const<T>::type, typename std::remove_const<U>::type>::value;

    template <typename T, typename U>
    concept NonSelfCopyConstructor = !(std::is_base_of_v<std::remove_cvref_t<T>, std::remove_cvref_t<U>> && std::is_base_of_v<std::remove_cvref_t<U>, std::remove_cvref_t<T>>);

    template <typename T>
    class WeakHandle;

    template <typename T>
    class ObjectHandle {
    private:
        template <typename U, std::size_t PageSize>
        friend class ObjectAllocator;

        template <typename U>
        friend class ObjectHandle;

        template <typename U>
        friend class WeakHandle;

        using deallocator_type = MemoryDeallocator;
        using count_getter_type = std::size_t&(*)(void*);

        ReferenceCounter *counter;
        T* object;

        template <typename U>
        static bool equals(ObjectHandle const& lhs, ObjectHandle<U> const& rhs);

        template <typename U>
        static bool equals(ObjectHandle const& lhs, WeakHandle<U> const& rhs);

        static void cleanupHandle(ReferenceCounter *counter) {

            counter->release();
            if (counter->getCount() <= 0) {
                counter->weakAcquire();
                auto deallocator = counter->getDeallocator();
                auto data = counter->getData();
                deallocator(data, DeallocationPhase::DESTROY);
                counter->weakRelease();

                if (counter->getWeakCount() <= 0) {
                    deallocator(data, DeallocationPhase::RELEASE);
                    ReferenceCounter::destroyReferenceCounter(counter);
                }
            }
        }

    public:
        explicit ObjectHandle(T *object_) : ObjectHandle(object_, new ImmediateReferenceCounter<T>(object_)) {}

        ObjectHandle(T* object_, MemoryControlBlock* counter_)
            : counter(new TypeReferenceCounter<T>(object_, counter_)), object(object_) {
            counter->acquire();
        }

        ObjectHandle(ReferenceCounter* counter_) : counter(counter_), object(reinterpret_cast<T*>(counter_->getData())) {
            counter->acquire();
        }

        ObjectHandle(T* object_, ReferenceCounter* counter_) : counter(counter_), object(object_) {
            counter->acquire();
        }

        template <typename U> requires (std::is_base_of_v<T, U> && !std::is_same_v<T, U>)
        ObjectHandle(U *object_) : ObjectHandle(object_, new ImmediateReferenceCounter<U>(object_)) {}

        ObjectHandle(T* object_, deallocator_type deallocator) : object(object_), counter(new ImmediateReferenceCounter<T>(object_, deallocator)) {
            counter->acquire();
        }

        ObjectHandle() : counter(EmptyReferenceCounter::getEmptyReferenceCounter()), object(nullptr) {
            counter->acquire();
        }

        ObjectHandle(std::nullptr_t) : ObjectHandle() {}

        ~ObjectHandle() {
            cleanupHandle(counter);
        }

        ObjectHandle(ObjectHandle const &other) : counter(other.counter), object(other.object) {
            counter->acquire();
        }

        ObjectHandle(ObjectHandle&& other) noexcept : ObjectHandle() {
            std::swap(object, other.object);
            std::swap(counter, other.counter);
        }

        ObjectHandle &operator=(ObjectHandle const &other) {
            if (this != &other) {
                other.counter->acquire();

                cleanupHandle(counter);

                object = other.object;
                counter = other.counter;
            }

            return *this;
        }

        ObjectHandle &operator=(ObjectHandle &&other) {
            if(this != &other) {
                std::swap(object, other.object);
                std::swap(counter, other.counter);

                other = nullptr;
            }
            return *this;
        }

        ObjectHandle& operator=(std::nullptr_t) {
            if (counter->getData() != nullptr) {
                auto new_counter = EmptyReferenceCounter::getEmptyReferenceCounter();
                new_counter->acquire();

                cleanupHandle(counter);

                counter = new_counter;
                object = nullptr;
            }

            return *this;
        }

        ObjectHandle& operator=(T *object_) {
            operator=(ObjectHandle(object_));
            return *this;
        }

        template <typename U> requires (std::is_base_of_v<T, U> && !std::is_same_v<T, U>)
        ObjectHandle& operator=(U *object_) {
            operator=(ObjectHandle<U>(object_));
            return *this;
        }

        template<typename U> requires ConvertibleObjectHandles<T, U>
        ObjectHandle(ObjectHandle<U> const& other) : counter(other.counter), object(other.object) {
            counter->acquire();
        }

        template<typename U> requires ConvertibleObjectHandles<T, U>
        ObjectHandle& operator=(ObjectHandle<U> const& other) {
            if (&other.getReferenceCounter() != counter) {
                other.counter->acquire();
                cleanupHandle(counter);

                counter = other.counter;
                object = other.object;
            }

            return *this;
        }

        T& operator*() const {
            return *object;
        }

        T * operator->() const {
            return object;
        }

        friend bool operator==(ObjectHandle const& lhs, std::nullptr_t) {
            return lhs.object == nullptr;
        }

        friend bool operator==(std::nullptr_t, ObjectHandle const& rhs) {
            return nullptr == rhs.object;
        }

            template <typename U> requires ComparableObjectHandles<T, U>
        friend bool operator==(ObjectHandle const& lhs, ObjectHandle<U> const& rhs) {
            return equals(lhs, rhs);
        }

        template <typename U> requires ComparableObjectHandles<T, U>
        friend bool operator==(ObjectHandle const& lhs, WeakHandle<U> const& rhs) {
            return equals(lhs, rhs);
        }

        template <typename U, typename = decltype(dynamic_cast<U*>(std::declval<T*>()))>
        friend ObjectHandle<U> dynamic_handle_cast(ObjectHandle const & src) {
            U* dst = dynamic_cast<U*>(src.object);
            if (dst != nullptr) {
                return ObjectHandle<U>(dst, src.counter);
            }
            return ObjectHandle<U>();
        }

        template <typename U, typename = decltype(static_cast<U*>(std::declval<T*>()))>
        friend ObjectHandle<U> static_handle_cast(ObjectHandle const & src) {
            return ObjectHandle<U>(static_cast<U*>(src.object), src.counter);
        }

        template <typename U, typename = decltype(const_cast<U*>(std::declval<T*>()))>
        friend ObjectHandle<U> const_handle_cast(ObjectHandle const& src) {
            return ObjectHandle<U>(const_cast<U*>(src.object), src.counter);
        }

        template <typename U, typename = decltype(reinterpret_cast<U*>(std::declval<T*>()))>
        friend ObjectHandle<U> reinterpret_handle_cast(ObjectHandle const& src) {
            return ObjectHandle<U>(reinterpret_cast<U*>(src.object), src.counter);
        }

        ReferenceCounter const& getReferenceCounter() const {
            return *counter;
        }
    };

    template <typename T>
    template <typename U>
    bool ObjectHandle<T>::equals(ObjectHandle<T> const& lhs, ObjectHandle<U> const& rhs) {
        return lhs.counter != nullptr && lhs.counter->equals(rhs.counter);
    }
}

#endif