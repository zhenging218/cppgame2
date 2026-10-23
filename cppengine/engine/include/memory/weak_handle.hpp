#ifndef WEAK_HANDLE_HPP
#define WEAK_HANDLE_HPP

#include "memory/object_handle.hpp"

namespace cppengine {

	template <typename T, typename U>
	concept ComparableWeakHandles = std::is_base_of<
		typename std::remove_const<T>::type,
		typename std::remove_const<U>::type
		>::value ||
		std::is_base_of<
		typename std::remove_const<U>::type,
		typename std::remove_const<T>::type
		>::value;

	template <typename T, typename U>
	concept ConvertibleWeakHandles = std::is_assignable<T*&, U*>::value &&
		!std::is_same<T, U>::value&& std::is_base_of<typename std::remove_const<T>::type, typename std::remove_const<U>::type>::value;

	template <typename T>
	class WeakHandle {
	private:
		using deallocator_type = MemoryDeallocator;

		template <typename U>
		friend class WeakHandle;

		template <typename U>
		friend class ObjectHandle;

		template <typename U, std::size_t PageSize>
		friend class ObjectAllocator;
		ReferenceCounter* counter;

		static void cleanupHandle(ReferenceCounter *counter) {
			counter->weakRelease();
			auto deallocator = counter->getDeallocator();
			if (counter->getCount() <= 0 && counter->getWeakCount() <= 0) {
				deallocator(counter->getData(), DeallocationPhase::RELEASE);
				ReferenceCounter::destroyReferenceCounter(counter);
			}
		}

		template <typename U>
		static bool equals(WeakHandle const& lhs, WeakHandle<U> const& rhs) {
			return lhs.counter == rhs.counter;
		}

		template <typename U>
		static bool equals(WeakHandle const& lhs, ObjectHandle<U> const& rhs);

	public:
		WeakHandle() : counter(EmptyReferenceCounter::getEmptyReferenceCounter()) {
			counter->weakAcquire();
		}

		WeakHandle(ObjectHandle<T> const& other) : counter(other.counter) {
			counter->weakAcquire();
		}

		WeakHandle(std::nullptr_t) : WeakHandle() {}

		WeakHandle(WeakHandle const& other) : counter(other.counter) {
			counter->weakAcquire();
		}

		WeakHandle(WeakHandle&& other) noexcept : WeakHandle() {
			std::swap(counter, other.counter);
		}

		WeakHandle& operator=(WeakHandle const& other) {
			if (this != &other) {
				other.counter->weakAcquire();

				cleanupHandle(counter);

				counter = other.counter;
			}

			return *this;
		}

		WeakHandle& operator=(WeakHandle&& other) noexcept {
			std::swap(counter, other.counter);
			return *this;
		}

		~WeakHandle() {
			cleanupHandle(counter);
		}

		template<typename U> requires ConvertibleWeakHandles<T, U>
		WeakHandle(WeakHandle<U> const& other) : counter(other.counter) {
			counter->weakAcquire();
		}

		template<typename U> requires ConvertibleWeakHandles<T, U>
		WeakHandle& operator=(WeakHandle<U> const& other) {
			if (counter != other.counter) {
				other.counter->weakAcquire();
				cleanupHandle(counter);
				counter = other.counter;
			}
			return *this;
		}

		template<typename U> requires ConvertibleWeakHandles<T, U>
		WeakHandle(ObjectHandle<U> const& other) : counter(other.counter) {
			counter->weakAcquire();
		}

		ObjectHandle<T> lock() const {
			if (counter->getCount() > 0) {
				return ObjectHandle<T>(counter);
			}
			return nullptr;
		}

		friend bool operator==(WeakHandle const& lhs, std::nullptr_t) {
			return lhs.counter->getCount() <= 0;
		}

		friend bool operator==(std::nullptr_t, WeakHandle const& rhs) {
			return rhs.counter->getCount() <= 0;
		}

		template <typename U> requires ComparableWeakHandles<T, U>
		friend bool operator==(WeakHandle const& lhs, WeakHandle<U> const& rhs) {
			return equals(lhs, rhs);
		}
	};

	template <typename T>
	template <typename U>
	bool ObjectHandle<T>::equals(ObjectHandle<T> const& lhs, WeakHandle<U> const& rhs) {
		return lhs.counter != nullptr && lhs.counter->equals(rhs);
	}

	template <typename T>
	template <typename U>
	bool WeakHandle<T>::equals(WeakHandle<T> const& lhs, ObjectHandle<U> const& rhs) {
		return lhs.counter == rhs.counter;
	}
}

#endif