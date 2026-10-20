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

SCENARIO("object_handle_create_test") {
    auto objectHandle = ObjectHandle(new TestObject{ .x = 1 });

    REQUIRE(objectHandle.getReferenceCounter().getCount() == 1);
    REQUIRE(objectHandle.getReferenceCounter().getWeakCount() == 0);
}