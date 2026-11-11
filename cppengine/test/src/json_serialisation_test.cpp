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
          INFO(oss.str());
        }
      }
    }
  }
}