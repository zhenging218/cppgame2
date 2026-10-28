//
// Created by Admin on 26/10/2026.
//

#include "test.hpp"
#include "memory/object_allocator.hpp"

#include <cstdint>
#include <ranges>

namespace {
    using namespace cppengine;

    struct AllocatedObject {
        std::uint16_t x;
    };

    template <typename T>
    using Allocator = ObjectAllocator<T>;
}

SCENARIO("allocators can be constructed") {
    GIVEN("An allocator") {

        Allocator<AllocatedObject> allocator;

        THEN("it initialises to an empty pool") {
            REQUIRE(allocator.getTotalPages() == 0);
            REQUIRE(allocator.getAllocatedBlockCount() == 0);
            REQUIRE(allocator.getAvailableBlockCount() == 0);
        }

        AND_WHEN("an object handle is created") {
            auto objectHandle = allocator.createHandle(43);

            THEN("pages are created") {
                REQUIRE(allocator.getTotalPages() > 0);
                REQUIRE(allocator.getAllocatedBlockCount() == 1);
            }
            AND_THEN("the allocated object aligns correctly") {
                REQUIRE(reinterpret_cast<std::uintptr_t>(&(*objectHandle)) % alignof(AllocatedObject) == 0);
            }
            AND_THEN("the allocated object is constructed correctly") {
                REQUIRE(objectHandle->x == 43);
            }
            AND_WHEN("another object handle is created") {
                auto objectHandle2 = allocator.createHandle(69);

                THEN("the object also uses memory from the allocator") {
                    REQUIRE(allocator.getAllocatedBlockCount() == 2);
                }
                AND_THEN("the object is also aligned correctly") {
                    REQUIRE(reinterpret_cast<std::uintptr_t>(&(*objectHandle2)) % alignof(AllocatedObject) == 0);
                }
                AND_THEN("the object is also constructed correctly") {
                    REQUIRE(objectHandle2->x == 69);
                }
                AND_THEN("the second object does not override the first object") {
                    REQUIRE(objectHandle != objectHandle2);
                    REQUIRE(&(*objectHandle) != &(*objectHandle2));
                }
            }
            AND_WHEN("the second object is out of scope") {
                THEN("the memory is returned to the allocator") {
                    REQUIRE(allocator.getAllocatedBlockCount() == 1);
                }
            }
        }
        AND_WHEN("the object handle is out of scope") {
            THEN("the memory is returned to the allocator") {
                REQUIRE(allocator.getAllocatedBlockCount() == 0);
            }
        }
    }
}

SCENARIO("object handles work for non polymorphic types using allocators") {
    GIVEN("an allocator") {
        auto allocator = Allocator<AllocatedObject>();
        AND_GIVEN("a allocator allocated object") {
            WHEN("managed with an object handle") {
                auto objectHandle = allocator.createHandle(42);

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
                        REQUIRE(allocator.getAllocatedBlockCount() == 1);
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
                        auto objectHandle2 = allocator.createHandle(70);

                        THEN("the handles are not equal") {
                            REQUIRE_FALSE(objectHandle == objectHandle2);
                        }
                        AND_THEN("the object is allocated from the same allocator") {
                            REQUIRE(allocator.getAllocatedBlockCount() == 2);
                        }
                        AND_WHEN("the first handle is assigned the second handle") {
                            REQUIRE_NOTHROW(objectHandle = objectHandle2);

                            THEN("the handles are now the same") {
                                REQUIRE(objectHandle == objectHandle2);
                                REQUIRE(objectHandle->x == 70);
                                REQUIRE(objectHandle->x == 70);
                            }
                            AND_THEN("the first object is deallocated") {
                                REQUIRE(allocator.getAllocatedBlockCount() == 1);
                            }
                        }
                        AND_WHEN("the second handle is move assigned to the first handle") {
                            REQUIRE_NOTHROW(objectHandle = std::move(objectHandle2));

                            THEN("the first object is deallocated") {
                                REQUIRE(allocator.getAllocatedBlockCount() == 1);
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
                    REQUIRE(allocator.getAllocatedBlockCount() == 0);
                }
            }
        }
    }
}

SCENARIO("weak handles work for non polymorphic types using allocators") {
    GIVEN("an allocator") {
        Allocator<AllocatedObject> allocator;
        AND_GIVEN("an object handle with a valid object") {
            auto objectHandle = allocator.createHandle(43);

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
                WeakHandle<AllocatedObject> weakHandle;

                {
                    auto objectHandle = allocator.createHandle(69);
                    weakHandle = objectHandle;
                }

                THEN("the weak handle's counter continues the track correctly") {
                    REQUIRE(weakHandle.getReferenceCounter().getCount() == 0);
                    REQUIRE(weakHandle.getReferenceCounter().getWeakCount() == 1);
                }
                AND_THEN("the object's memory cannot be used until all counters are cleared") {
                    REQUIRE(allocator.getAllocatedBlockCount() == 1);
                }
                AND_THEN("the weak handle can be locked and return an empty handle") {
                    ObjectHandle<AllocatedObject> objectHandle;

                    REQUIRE_NOTHROW([&weakHandle, &objectHandle]() { objectHandle = weakHandle.lock(); }());
                    REQUIRE(objectHandle == nullptr);
                }
            }
            AND_WHEN("the weak handle is out of scope") {
                THEN("the memory is returned to the allocator") {
                    REQUIRE(allocator.getAllocatedBlockCount() == 0);
                }
            }
        }
    }
}

SCENARIO("allocators allow mutating allocated objects via visitation") {
    GIVEN("an allocator") {
        auto allocator = Allocator<AllocatedObject>();

        AND_GIVEN("some objects that are allocated") {
            auto objectHandle = allocator.createHandle(1);
            auto objectHandle2 = allocator.createHandle(2);
            auto objectHandle3 = allocator.createHandle(3);
            auto objectHandle4 = allocator.createHandle(4);

            WHEN("a visitor with a visit counter sets values on the allocated object") {
                int visits = 0;

                allocator.visit([&visits](auto &object) {
                    object.x = 69;
                    ++visits;
                });

                THEN("the amount of visitations match the number of allocated objects") {
                    REQUIRE(visits == allocator.getAllocatedBlockCount());
                }
                AND_THEN("the objects are mutated") {
                    REQUIRE(objectHandle->x == 69);
                    REQUIRE(objectHandle2->x == 69);
                    REQUIRE(objectHandle3->x == 69);
                    REQUIRE(objectHandle4->x == 69);
                }
            }
        }
    }
}
