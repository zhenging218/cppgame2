//
// Created by Admin on 18/10/2026.
//

#include "test.hpp"

using namespace cppengine;

namespace {
    struct Plain {
        int x, y;
    };

    struct Unregistered {
        int x, y;
    };

    struct Registered {
        int x, y;
    };
}

DECL_TYPE_DESCRIPTOR(Unregistered);
DECL_TYPE_DESCRIPTOR(Registered);

DECL_TYPE_MEMBERS(Registered)
    DECL_TYPE_MEMBER(x),
    DECL_TYPE_MEMBER(y)
END_DECL_TYPE_MEMBERS()

SCENARIO("unregistered_type_test") {
    GIVEN("An unregistered type") {
        REQUIRE_FALSE(TypeTraits<Plain>::defined_trait_v);

        AND_GIVEN("its type descriptor") {
            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<Plain>();
            WHEN("its member list is queried") {
                const auto fields = descriptor->getFields();

                THEN("the fields list is empty") {
                    REQUIRE(fields.size() == 0);
                }
            }
        }
    }
}

SCENARIO("registered_type_no_registered_members_test") {
    GIVEN("A registered type with members not registered") {
        REQUIRE(TypeTraits<Unregistered>::defined_trait_v);

        AND_GIVEN("its type descriptor") {
            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<Unregistered>();

            WHEN("its member list is queried") {
                const auto fields = descriptor->getFields();

                THEN("the fields list is empty") {
                    REQUIRE(fields.size() == 0);
                }
            }
        }
    }
}

SCENARIO("registered_type_with_registered_members_test") {
    GIVEN("A registered type with members registered") {
        REQUIRE(TypeTraits<Registered>::defined_trait_v);

        AND_GIVEN("its type descriptor") {
            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<Registered>();

            WHEN("its member list is queried") {
                const auto fields = descriptor->getFields();

                THEN("the size of the field list is the same as the number of the registered fields") {
                    REQUIRE(fields.size() == 2);
                }

                AND_WHEN("the member list is read") {

                    THEN("each member's names can be retrieved correctly") {
                        REQUIRE(strcmp(fields[0].getName(), "x") == 0);
                        REQUIRE(strcmp(fields[1].getName(), "y") == 0);
                    }
                }
            }
        }
    }
}