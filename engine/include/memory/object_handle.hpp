#pragma once

#include <type_traits>

#include "memory/reference_counter.hpp"


namespace cppengine {
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

        using deallocator_type = void(*)(void*);
        using count_getter_type = std::size_t&(*)(void*);

        ReferenceCounter *counter;
        T* object;

        template <typename U>
        static bool equals(ObjectHandle const& lhs, ObjectHandle<U> const& rhs);

        template <typename U>
        static bool equals(ObjectHandle const& lhs, WeakHandle<U> const& rhs);

    public:
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

        ObjectHandle(T* object_) : object(object_), counter(new ImmediateReferenceCounter<T>(object_)) {
            counter->acquire();
        }

        ObjectHandle(T* object_, deallocator_type deallocator) : object(object_), counter(new ImmediateReferenceCounter<T>(object_, deallocator)) {
            counter->acquire();
        }

        ObjectHandle() : counter(new EmptyReferenceCounter()), object(nullptr) {
            counter->acquire();
        }

        ObjectHandle(std::nullptr_t) : ObjectHandle() {}

        ~ObjectHandle() {
            counter->release();
            if (counter->getCount() <= 0) {
                auto deallocator = counter->getDeallocator();
                deallocator(reinterpret_cast<void*>(const_cast<typename std::remove_const<T>::type*>(object)));

                if (counter->getWeakCount() <= 0) {
                    delete counter;
                }
            }
        }

        ObjectHandle(ObjectHandle const &other) : counter(other.counter), object(other.object) {
            counter->acquire();
        }

        ObjectHandle(ObjectHandle&& other) noexcept : ObjectHandle() {
            std::swap(object, other.object);
            std::swap(counter, other.counter);
        }

        ObjectHandle &operator=(ObjectHandle const &other) {
            counter->release();

            if (counter->getCount() <= 0) {
                (counter->getDeallocator())(reinterpret_cast<void*>(const_cast<typename std::remove_const<T>::type*>(object)));

                if (counter->getWeakCount() <= 0) {
                    delete counter;
                }
            }

            object = other.object;
            counter = other.counter;
            counter->acquire();

            return *this;
        }

        ObjectHandle &operator=(ObjectHandle &&other) noexcept {
            std::swap(object, other.object);
            std::swap(counter, other.counter);

            return *this;
        }

        ObjectHandle& operator=(std::nullptr_t) {
            counter->release();

            if (counter->getCount() <= 0) {
                (counter->getDeallocator())(reinterpret_cast<void*>(const_cast<typename std::remove_const<T>::type*>(object)));

                if (counter->getWeakCount() <= 0) {
                    delete counter;
                }
            }

            counter = new EmptyReferenceCounter();
            object = nullptr;
            counter->acquire();

            return *this;
        }

        template<typename U, typename = typename std::enable_if<std::is_assignable<T*&, U*>::value &&
            !std::is_same<T, U>::value && std::is_base_of<typename std::remove_const<T>::type, typename std::remove_const<U>::type>::value>::type>
        ObjectHandle(ObjectHandle<U> const& other) : counter(other.counter), object(other.object) {
            counter->acquire();
        }

        template<typename U, typename = typename std::enable_if<std::is_assignable<T*&, U*>::value &&
            !std::is_same<T, U>::value && std::is_base_of<typename std::remove_const<T>::type, typename std::remove_const<U>::type>::value>::type>
        ObjectHandle& operator=(ObjectHandle<U> const& other) {
            counter->release();

            if (counter->getCount() <= 0) {
                (counter->getDeallocator())(reinterpret_cast<void*>(object));
                delete counter;
            }

            object = other.object;
            counter = other.counter;
            counter->acquire();

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

        template <typename U, typename = typename std::enable_if<
            std::is_base_of<
            typename std::remove_const<T>::type,
            typename std::remove_const<U>::type
            >::value ||
            std::is_base_of<
            typename std::remove_const<U>::type,
            typename std::remove_const<T>::type
            >::value
        >::type>
        friend bool operator==(ObjectHandle const& lhs, ObjectHandle<U> const& rhs) {
            return equals(lhs, rhs);
        }

        template <typename U, typename = typename std::enable_if<
            std::is_base_of<
            typename std::remove_const<T>::type,
            typename std::remove_const<U>::type
            >::value ||
            std::is_base_of<
            typename std::remove_const<U>::type,
            typename std::remove_const<T>::type
            >::value
        >::type>
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

        template <typename ... Args>
        friend ObjectHandle createHandle(Args &&... args);
    };

    template <typename T>
    template <typename U>
    bool ObjectHandle<T>::equals(ObjectHandle<T> const& lhs, ObjectHandle<U> const& rhs) {
        return lhs.counter == rhs.counter;
    }

    template <typename T, typename ... Args>
    ObjectHandle<T> createHandle(Args &&... args) {
        return ObjectHandle<T>(new T{std::forward<Args>(args)...});
    }

    template <typename T>
    ObjectHandle<T> wrapWithHandle(T *obj) {
        return ObjectHandle<T>(obj, new UnownedTypeReference<T>());
    }
}