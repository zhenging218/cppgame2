//
// Created by zyiu on 11/11/2026.
//

#include <map>
#include <set>
#include <unordered_map>
#include <string>

#include "test.hpp"

namespace {
  struct Test {
    int x = 0;
    std::string y = "hello";
    int z[10] {0};
    std::map<std::string, float> w { {"hi", 0.5f}, {"yo", 1.3f} };
    std::set<int> u { 69, 420 };
    std::unordered_map<int, std::string> v { { 67, "hihi" }, { 1337, "bye" } };

    private:
      int i = 555;

    public:
      int const &getI() const { return i; }
      void setI(int i_) { i = i_; }
  };
}

DECL_TYPE_DESCRIPTOR(Test);

DECL_TYPE_MEMBERS(Test)
    DECL_TYPE_MEMBER_FIELD(x),
    DECL_TYPE_MEMBER_FIELD(y),
    DECL_TYPE_MEMBER_FIELD(z),
    DECL_TYPE_MEMBER_FIELD(w),
    DECL_TYPE_MEMBER_FIELD(u),
    DECL_TYPE_MEMBER_FIELD(v),
    DECL_TYPE_MEMBER_ACCESSORS(i, getI, setI)
END_DECL_TYPE_MEMBERS();

using namespace cppengine;

SCENARIO("Objects can be serialised if registered") {
  GIVEN("a registered object") {
    Test test;

    AND_GIVEN("a serialiser") {
      std::ostringstream oss;
      auto serialiser = Serialiser::createJsonSerialiser(oss);

      WHEN("the object is serialised") {
        REQUIRE_NOTHROW(serialiser->serialise(test));

        THEN("the serialisation is successful") {
          auto payload = oss.str();

          AND_GIVEN("another object") {
            Test test2;
            test2.x = 7;
            test2.y = "bye";

            for (int & i : test2.z) {
              i = 20;
            }

            test2.w = { { "yohoho", 3.14f } };
            test2.u = { 369 };
            test2.v = { {123, "foo" }, { 456, "bar" } };

            test2.setI(666);

            AND_GIVEN("a deserialiser") {
              std::istringstream iss(payload);
              auto deserialiser = Deserialiser::createJsonDeserialiser(iss);

              WHEN("the payload is desrialised") {
                REQUIRE_NOTHROW(deserialiser->deserialise(test2));

                THEN("the other object takes the values of the payload") {
                  REQUIRE(test2.x == 0);

                }
              }
            }
          }
        }
      }
    }
  }
}