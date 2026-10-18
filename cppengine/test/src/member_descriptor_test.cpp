//
// Created by Admin on 18/10/2026.
//

#include "test.hpp"

using namespace cppengine;

namespace {
    constexpr float epsilon = std::numeric_limits<float>::epsilon();

    struct Plain {
        int x;
        float y;
    };

    struct Unregistered {
        int x;
        float y;
    };

    struct Registered {
        int x;
        float y;
    };

    struct RegisteredConst {
        const int x;
    };
}

DECL_TYPE_DESCRIPTOR(Unregistered);
DECL_TYPE_DESCRIPTOR(Registered);
DECL_TYPE_DESCRIPTOR(RegisteredConst);

DECL_TYPE_MEMBERS(Registered)
    DECL_TYPE_MEMBER(x),
    DECL_TYPE_MEMBER(y)
END_DECL_TYPE_MEMBERS()

DECL_TYPE_MEMBERS(RegisteredConst)
    DECL_TYPE_MEMBER(x)
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

                AND_GIVEN("an object of the registered type") {
                    Registered registered { .x = 1, .y = 2 };

                    WHEN("the field list is used to get the member values") {
                        auto x = static_cast<int *>(fields[0].get(&registered));
                        auto y = static_cast<float *>(fields[1].get(&registered));

                        THEN("The values can be retrieved successfully") {
                            REQUIRE(*x == 1);
                            REQUIRE(std::abs(2 - *y) < epsilon);
                        }
                    }
                    AND_WHEN("the field list is used to get the member values as from a const version of the object") {
                        auto x = static_cast<int const *>(fields[0].get(const_cast<Registered const *>(&registered)));
                        auto y = static_cast<float const *>(fields[1].get(const_cast<Registered const *>(&registered)));

                        THEN("The values can be retrieved successfully") {
                            REQUIRE(*x == 1);
                            REQUIRE(std::abs(2 - *y) < epsilon);
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("registered_type_with_const_registered_members_test") {
    GIVEN("A registered type with members registered") {
        REQUIRE(TypeTraits<RegisteredConst>::defined_trait_v);

        AND_GIVEN("its type descriptor") {
            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<RegisteredConst>();

            WHEN("its member list is queried") {
                const auto fields = descriptor->getFields();

                THEN("the size of the field list is the same as the number of the registered fields") {
                    REQUIRE(fields.size() == 1);
                }

                AND_WHEN("the member list is read") {

                    THEN("each member's names can be retrieved correctly") {
                        REQUIRE(strcmp(fields[0].getName(), "x") == 0);
                    }
                }

                AND_GIVEN("an object of the registered type") {
                    RegisteredConst registered { .x = 1};

                    WHEN("the field list is used to get the member values as from a const version of the object") {
                        auto x = static_cast<int const *>(fields[0].get(const_cast<RegisteredConst const *>(&registered)));

                        THEN("The values can be retrieved successfully") {
                            REQUIRE(x != nullptr);
                            REQUIRE(*x == 1);
                        }
                    }
                    AND_WHEN("the field list is used to get the member values") {
                        auto x = static_cast<int *>(fields[0].get(&registered));

                        THEN("The value cannot be retrieved") {
                            REQUIRE(x == nullptr);
                        }
                    }
                }
            }
        }
    }
}