#include "memory/objects.hpp"

namespace cppengine {
    void dummyDeallocator(void*) {}

    ReferenceCounter::ReferenceCounter() {}
    ReferenceCounter::~ReferenceCounter() {}

    EmptyReferenceCounter::EmptyReferenceCounter()
        : ReferenceCounter(), count(0), weakCount(0) {

    }

    void EmptyReferenceCounter::acquire() {
        ++count;
    }

    void EmptyReferenceCounter::release() {
        --count;
    }

    void EmptyReferenceCounter::weakAcquire() {
        ++weakCount;
    }

    void EmptyReferenceCounter::weakRelease() {
        --weakCount;
    }

    void* EmptyReferenceCounter::getData() const {
        return nullptr;
    }

    std::size_t EmptyReferenceCounter::getCount() const {
        return count;
    }

    std::size_t EmptyReferenceCounter::getWeakCount() const {
        return weakCount;
    }

    ReferenceCounter::deallocator_type EmptyReferenceCounter::getDeallocator() const {
        return &dummyDeallocator;
    }
}