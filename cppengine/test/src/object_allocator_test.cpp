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
