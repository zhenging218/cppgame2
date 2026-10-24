//
// Created by Admin on 20/10/2026.
//

#include "test.hpp"
#include "memory/object_handle.hpp"

namespace {
    int objectCount = 0;
    int allocations = 0;
    int deallocations = 0;

    struct TestObject {
        int x;
        TestObject(int x_) : x(x_) {
            ++objectCount;
        }

        TestObject(TestObject const &) = delete;
        TestObject(TestObject &&) noexcept = delete;

        TestObject &operator=(TestObject const &) = delete;
        TestObject &operator=(TestObject &&) noexcept = delete;

        virtual ~TestObject() {
            --objectCount;
        }

        static void * operator new(std::size_t size) {
            void *result = std::malloc(size);
            allocations++;
            return result;
        }

        static void operator delete(void *ptr) noexcept {
            std::free(ptr);
            deallocations++;
        }
    };
}

using namespace cppengine;

SCENARIO("object handles work for non polymorphic types") {
    GIVEN("a heap allocated object") {
        WHEN("managed with an object handle") {
            auto objectHandle = ObjectHandle(new TestObject(42));

            THEN("the object handle is not equal to a nullptr") {
                REQUIRE_FALSE(objectHandle == nullptr);
            }
            AND_THEN("the object handle points to the correct object") {
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
                AND_THEN("the copied handle does not allocate an additional object") {
                    REQUIRE(objectCount == 1);
                }
                AND_THEN("the copied handle points to the same object") {
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
                    REQUIRE(objectHandle->x == 42);
                }
            }
            AND_GIVEN("a second heap allocated object") {
                WHEN("also managed with an object handle") {
                    auto objectHandle2 = createHandle<TestObject>(70);

                    THEN("the handles are not equal") {
                        REQUIRE_FALSE(objectHandle == objectHandle2);
                    }
                    AND_WHEN("the first handle is assigned the second handle") {
                        REQUIRE_NOTHROW(objectHandle = objectHandle2);

                        THEN("the handles are now the same") {
                            REQUIRE(objectHandle == objectHandle2);
                            REQUIRE(objectHandle->x == 70);
                            REQUIRE(objectHandle->x == 70);
                        }
                        AND_THEN("the first object is deallocated") {
                            REQUIRE(objectCount == 1);
                        }
                    }
                    AND_WHEN("the second handle is move assigned to the first handle") {
                        REQUIRE_NOTHROW(objectHandle = std::move(objectHandle2));

                        THEN("the first object is deallocated") {
                            REQUIRE(objectCount == 1);
                        }
                        AND_THEN("the second handle is now empty") {
                            REQUIRE(objectHandle2 == nullptr);
                        }
                        AND_THEN("the first handle now manages the second object") {
                            REQUIRE(objectHandle->x == 70);
                        }
                    }
                }
            }
        }
        AND_WHEN("no handles remain in scope") {
            THEN("no objects are alive") {
                REQUIRE(objectCount == 0);
            }
            AND_THEN("no memory is leaked") {
                REQUIRE(allocations == deallocations);
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

SCENARIO("weak handles work for non polymorphic types") {
    GIVEN("an object handle with a valid object") {
        auto objectHandle = createHandle<TestObject>(43);

        WHEN("a weak handle is acquired") {
            WeakHandle weakHandle = objectHandle;

            THEN("the handles are equal") {
                REQUIRE(objectHandle == weakHandle);
            }
            AND_THEN("the strong count is not incremented") {
                REQUIRE(objectHandle.getReferenceCounter().getCount() == 1);
            }
            AND_THEN("the weak count is incremented") {
                REQUIRE(objectHandle.getReferenceCounter().getWeakCount() == 1);
            }
            AND_WHEN("the weak handle is locked") {
                auto objectHandle2 = weakHandle.lock();

                THEN("the acquired object handle is valid") {
                    REQUIRE(objectHandle2 != nullptr);
                    REQUIRE(objectHandle2->x == 43);
                }
                AND_THEN("the reference count is updated accordingly") {
                    REQUIRE(objectHandle.getReferenceCounter().getCount() == 2);
                    REQUIRE(objectHandle.getReferenceCounter().getWeakCount() == 1);

                    REQUIRE(weakHandle.getReferenceCounter().getCount() == 2);
                    REQUIRE(weakHandle.getReferenceCounter().getWeakCount() == 1);
                }
            }
            AND_WHEN("the object handle acquired from lock is out of scope") {
                THEN("the reference count is updated again accordingly") {
                    REQUIRE(objectHandle.getReferenceCounter().getCount() == 1);
                    REQUIRE(objectHandle.getReferenceCounter().getWeakCount() == 1);
                }
            }
        }
        AND_WHEN("the weak handle is out of scope") {
            THEN("the reference count is updated accordingly") {
                REQUIRE(objectHandle.getReferenceCounter().getCount() == 1);
                REQUIRE(objectHandle.getReferenceCounter().getWeakCount() == 0);
            }
        }
    }
    AND_GIVEN("an object handle") {
        WHEN("a weak handle is acquired and then the object handle is out of scope") {
            WeakHandle<TestObject> weakHandle;

            {
                auto objectHandle = createHandle<TestObject>(69);
                weakHandle = objectHandle;
            }

            THEN("the weak handle's counter continues the track correctly") {
                REQUIRE(weakHandle.getReferenceCounter().getCount() == 0);
                REQUIRE(weakHandle.getReferenceCounter().getWeakCount() == 1);
            }
            AND_THEN("the weak handle can be locked and return an empty handle") {
                ObjectHandle<TestObject> objectHandle;

                REQUIRE_NOTHROW([&weakHandle, &objectHandle]() { objectHandle = weakHandle.lock(); }());
                REQUIRE(objectHandle == nullptr);
            }
        }
        AND_WHEN("the weak handle is out of scope") {
            THEN("the object does not get deallocated again") {
                REQUIRE(allocations == deallocations);
            }
        }
    }
}