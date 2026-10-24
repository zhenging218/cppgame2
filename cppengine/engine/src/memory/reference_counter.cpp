#include "memory/objects.hpp"

namespace cppengine {
    void dummyDeallocator(void*, void*, DeallocationPhase) {}

    ReferenceCounter::ReferenceCounter() {}
    ReferenceCounter::~ReferenceCounter() {}

    EmptyReferenceCounter *EmptyReferenceCounter::getEmptyReferenceCounter() {
        static EmptyReferenceCounter emptyReferenceCounter;
        return &emptyReferenceCounter;
    }

    void ReferenceCounter::destroyReferenceCounter(ReferenceCounter *counter) {
        if (counter != EmptyReferenceCounter::getEmptyReferenceCounter() && counter != nullptr) {
            delete counter;
        }
    }



    EmptyReferenceCounter::EmptyReferenceCounter()
        : count(0), weakCount(0) {

    }

    void EmptyReferenceCounter::acquire() {

    }

    void EmptyReferenceCounter::release() {

    }

    void EmptyReferenceCounter::weakAcquire() {

    }

    void EmptyReferenceCounter::weakRelease() {

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
        return {&dummyDeallocator};
    }
}
