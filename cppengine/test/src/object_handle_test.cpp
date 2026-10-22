//
// Created by Admin on 20/10/2026.
//

#include "test.hpp"
#include "memory/object_handle.hpp"

namespace {
    struct TestObject {
        int x;
    };
}

using namespace cppengine;

SCENARIO("object handles pointing to the same type should be constructible") {
    GIVEN("a heap allocated object") {
        auto object = new TestObject{ .x = 42 };

        WHEN("managed with an object handle") {
            auto objectHandle = ObjectHandle(object);

            THEN("the object handle is not equal to a nullptr") {
                REQUIRE_FALSE(objectHandle == nullptr);
            }
            AND_THEN("the object handle points to the correct object") {
                REQUIRE((&(*objectHandle)) == object);
                REQUIRE(objectHandle->x == 42);
            }
            AND_THEN("the object handle's reference count is correct") {
                REQUIRE(objectHandle.getReferenceCounter().getCount() == 1);
                REQUIRE(objectHandle.getReferenceCounter().getWeakCount() == 0);
            }
            AND_GIVEN("a copied handle") {
                auto objectHandle2 = objectHandle;

                THEN("the copied handle is not equal to a nullptr") {
                    REQUIRE_FALSE(objectHandle2 == nullptr);
                }
                AND_THEN("the copied handle points to the same object") {
                    REQUIRE((&(*objectHandle2)) == object);
                    REQUIRE(objectHandle2->x == 42);
                }
                AND_THEN("the copied handle equals to the frist handle") {
                    REQUIRE(objectHandle == objectHandle2);
                }
                AND_THEN("the reference count is incremented") {
                    REQUIRE(objectHandle.getReferenceCounter().getCount() == 2);
                    REQUIRE(objectHandle.getReferenceCounter().getWeakCount() == 0);
                    REQUIRE(objectHandle2.getReferenceCounter().getCount() == 2);
                    REQUIRE(objectHandle2.getReferenceCounter().getWeakCount() == 0);
                }
            }
            AND_WHEN("the copied handle is destroyed") {
                THEN("the reference count is decremented") {
                    REQUIRE(objectHandle.getReferenceCounter().getCount() == 1);
                    REQUIRE(objectHandle.getReferenceCounter().getWeakCount() == 0);
                }
                AND_THEN("the first handle is still valid") {
                    REQUIRE((&(*objectHandle)) == object);
                    REQUIRE(objectHandle->x == 42);
                }
            }
        }
    }
}

SCENARIO("reference counters for nullptr should use a single global instance") {
    GIVEN("two reference counter pointers returned by the global empty reference counter getter") {
        auto const *counter = EmptyReferenceCounter::getEmptyReferenceCounter();
        auto const *counter2 = EmptyReferenceCounter::getEmptyReferenceCounter();

        THEN("both counters point to the same object") {
            REQUIRE(counter == counter2);
        }
    }
}

SCENARIO("object handles should support nullptr") {
    GIVEN("a default constructed object handle") {
        auto defaultHandle = ObjectHandle<TestObject>();

        THEN("the handle points to a nullptr") {
            REQUIRE(defaultHandle == nullptr);
        }
        AND_THEN("the handle does not count references") {
            REQUIRE(defaultHandle.getReferenceCounter().getCount() == 0);
            REQUIRE(defaultHandle.getReferenceCounter().getWeakCount() == 0);
        }
        AND_GIVEN("another default constructed object handle") {
            auto defaultHandle2 = ObjectHandle<TestObject>();

            THEN("the handles are equal") {
                REQUIRE(defaultHandle == defaultHandle2);
            }
            AND_THEN("the reference counters do no increment") {
                REQUIRE(defaultHandle.getReferenceCounter().getCount() == 0);
                REQUIRE(defaultHandle.getReferenceCounter().getWeakCount() == 0);
                REQUIRE(defaultHandle2.getReferenceCounter().getCount() == 0);
                REQUIRE(defaultHandle2.getReferenceCounter().getWeakCount() == 0);
            }
            AND_GIVEN("the reference counters of both handles") {
                const auto &defaultReferenceCounter = defaultHandle.getReferenceCounter();
                const auto &defaultReferenceCounter2 = defaultHandle2.getReferenceCounter();

                THEN("both reference counters point to the global empty reference counter") {
                    REQUIRE(&defaultReferenceCounter == EmptyReferenceCounter::getEmptyReferenceCounter());
                    REQUIRE(&defaultReferenceCounter2 == EmptyReferenceCounter::getEmptyReferenceCounter());
                }
            }
        }
        AND_WHEN("the second handle is out of scope") {
            THEN("the reference counter do not decrement") {
                REQUIRE(defaultHandle.getReferenceCounter().getCount() == 0);
                REQUIRE(defaultHandle.getReferenceCounter().getWeakCount() == 0);
            }
        }
    }
}