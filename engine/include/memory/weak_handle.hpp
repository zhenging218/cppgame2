#pragma once

#include "memory/object_handle.hpp"

template <typename T>
class WeakHandle {
private:
	template <typename U>
	friend class WeakHandle;

	template <typename U>
	friend class ObjectHandle;

	template <typename U, std::size_t PageSize>
	friend class ObjectAllocator;

	ReferenceCounter* counter;

	template <typename U>
	static bool equals(WeakHandle const& lhs, WeakHandle<U> const& rhs) {
		return lhs.counter == rhs.counter;
	}

	template <typename U>
	static bool equals(WeakHandle const& lhs, ObjectHandle<U> const& rhs);

public:
	WeakHandle() : counter(new EmptyReferenceCounter()) {
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
		counter->weakRelease();

		counter = other.counter;
		counter->weakAcquire();
		return *this;
	}

	WeakHandle& operator=(WeakHandle&& other) {
		std::swap(counter, other.counter);
		return *this;
	}

	~WeakHandle() {
		counter->weakRelease();
	}

	template<typename U, typename = typename std::enable_if<std::is_assignable<T*&, U*>::value &&
		!std::is_same<T, U>::value&& std::is_base_of<typename std::remove_const<T>::type, typename std::remove_const<U>::type>::value>::type>
	WeakHandle(WeakHandle<U> const& other) : counter(other.counter) {
		counter->weakAcquire();
	}

	template<typename U, typename = typename std::enable_if<std::is_assignable<T*&, U*>::value &&
		!std::is_same<T, U>::value&& std::is_base_of<typename std::remove_const<T>::type, typename std::remove_const<U>::type>::value>::type>
	WeakHandle& operator=(WeakHandle<U> const& other) {
		counter->weakRelease();
		counter = other.counter;
		counter->weakAcquire();
		return *this;
	}

	template<typename U, typename = typename std::enable_if<std::is_assignable<T*&, U*>::value &&
		!std::is_same<T, U>::value&& std::is_base_of<typename std::remove_const<T>::type, typename std::remove_const<U>::type>::value>::type>
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
	friend bool operator==(WeakHandle const& lhs, WeakHandle<U> const& rhs) {
		return equals(lhs, rhs);
	}
};

template <typename T>
template <typename U>
bool ObjectHandle<T>::equals(ObjectHandle<T> const& lhs, WeakHandle<U> const& rhs) {
	return lhs.counter == rhs.counter;
}

template <typename T>
template <typename U>
bool WeakHandle<T>::equals(WeakHandle<T> const& lhs, ObjectHandle<U> const& rhs) {
	return lhs.counter == rhs.counter;
}