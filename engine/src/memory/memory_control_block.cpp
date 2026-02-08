#include "memory/objects.hpp"

namespace cppengine {
	MemoryControlBlock::MemoryControlBlock(deallocator_pointer deallocator_)
		: active(false), acquireCount(0), weakAcquireCount(0), deallocator(deallocator_) {}

	std::size_t MemoryControlBlock::getAcquireCount() const {
		return acquireCount;
	}

	std::size_t MemoryControlBlock::getWeakAcquireCount() const {
		return weakAcquireCount;
	}

	MemoryControlBlock::deallocator_pointer MemoryControlBlock::getDeallocator() const {
		return deallocator;
	}

	void MemoryControlBlock::acquire() {
		++acquireCount;
	}

	void MemoryControlBlock::release() {
		--acquireCount;
	}

	void MemoryControlBlock::weakAcquire() {
		++weakAcquireCount;
	}

	void MemoryControlBlock::weakRelease() {
		--weakAcquireCount;
	}
}