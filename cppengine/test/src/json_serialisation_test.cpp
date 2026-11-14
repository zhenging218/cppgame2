//
// Created by zyiu on 11/11/2026.
//

#include <map>
#include <set>
#include <unordered_map>
#include <string>

#include "test.hpp"

namespace {
  using namespace cppengine;

  struct Test {
    int x = 0;
    std::string y;
    int z[10] {0};
    std::map<std::string, float> w;
    std::set<int> u;
    std::unordered_map<int, std::string> v;
    std::vector<Uniform> r;

    private:
      int i = 0;

    public:
      Test() = default;

      Test(int x_,
           std::string y_,
           const std::array<int, 10>& z_,
           std::map<std::string, float> w_,
           std::set<int> u_,
           std::unordered_map<int, std::string> v_,
           std::vector<Uniform> r_,
           int i_)
        : x(x_), y(std::move(y_)),
          w(std::move(w_)), u(std::move(u_)), v(std::move(v_)), r(std::move(r_)),
          i(i_)
      {
        std::copy(z_.begin(), z_.end(), z);
      }

      int const &getI() const { return i; }
      void setI(int i_) { i = i_; }

      friend bool operator==(Test const &lhs, Test const &rhs);
      friend bool operator!=(Test const &lhs, Test const &rhs);
  };

  bool operator==(Test const &lhs, Test const &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && std::equal(lhs.z, lhs.z + 10, rhs.z) &&
           std::ranges::equal(lhs.w, rhs.w, [](auto const &a, auto const &b)
           { return a.first == b.first && std::abs(b.second - a.second) < 1e-5f; })
    && lhs.u == rhs.u && lhs.v == rhs.v  && lhs.r == rhs.r && lhs.i == rhs.i;
  }

  bool operator!=(Test const &lhs, Test const &rhs) {
    return !(lhs == rhs);
  }

  std::string serialiseToString(Test const &obj) {
    std::ostringstream oss;
    auto serialiser = Serialiser::createJsonSerialiser(oss);
    REQUIRE_NOTHROW(serialiser->serialise(obj));
    return oss.str();
  }

  void deserialiseFromString(std::string const &payload, Test &target) {
    std::istringstream iss(payload);
    auto deserialiser = Deserialiser::createJsonDeserialiser(iss);
    REQUIRE_NOTHROW(deserialiser->deserialise(target));
  }

  size_t countOccurrences(std::string const &haystack, std::string const &needle) {
    size_t count = 0, pos = 0;
    while ((pos = haystack.find(needle, pos)) != std::string::npos) {
      ++count;
      pos += needle.size();
    }
    return count;
  }
}

DECL_TYPE_DESCRIPTOR(Test);

DECL_TYPE_MEMBERS(Test)
    DECL_TYPE_MEMBER_FIELD(x),
    DECL_TYPE_MEMBER_FIELD(y),
    DECL_TYPE_MEMBER_FIELD(z),
    DECL_TYPE_MEMBER_FIELD(w),
    DECL_TYPE_MEMBER_FIELD(u),
    DECL_TYPE_MEMBER_FIELD(v),
    DECL_TYPE_MEMBER_FIELD(r),
    DECL_TYPE_MEMBER_ACCESSORS(i, getI, setI)
END_DECL_TYPE_MEMBERS();

using namespace cppengine;

SCENARIO("Objects can be serialised if registered") {
  GIVEN("a registered object") {
    Test test = Test{
      0,
      "hello",
      {},                                        // all zeros
      { {"hi", 0.5f}, {"yo", 1.3f} },
      { 69, 420 },
      { {67, "hihi"}, {1337, "bye"} },
      { Vector2{123,456}, 7 },
      555
    };

    AND_GIVEN("a serialiser") {
      std::ostringstream oss;
      auto serialiser = Serialiser::createJsonSerialiser(oss);

      WHEN("the object is serialised") {
        REQUIRE_NOTHROW(serialiser->serialise(test));

        THEN("the serialisation is successful") {
          auto payload = oss.str();

          AND_GIVEN("another object") {
            Test test2 = Test{
              42,
              "populated",
              {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
              { {"alpha", 0.25f}, {"beta", -1.5f}, {"gamma", 100.0f} },
              { -5, 0, 7, 1000 },
              { {1, "one"}, {2, "two"}, {-3, "minus three"} },
              { Vector2{7,12}, 25 },
              999
            };

            REQUIRE(test2 != test);

            AND_GIVEN("a deserialiser") {
              std::istringstream iss(payload);
              auto deserialiser = Deserialiser::createJsonDeserialiser(iss);

              WHEN("the payload is deserialised") {
                REQUIRE_NOTHROW(deserialiser->deserialise(test2));

                THEN("the other object takes the values of the payload") {
                  REQUIRE(test2 == test);
                }
              }
            }
          }
        }
      }
    }
  }
}

SCENARIO("Serialised objects survive a round trip") {
  GIVEN("the object") {
    Test original = Test{
      42,
      "populated",
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
      { {"alpha", 0.25f}, {"beta", -1.5f}, {"gamma", 100.0f} },
      { -5, 0, 7, 1000 },
      { {1, "one"}, {2, "two"}, {-3, "minus three"} },
      { Vector2{7,12}, 25 },
      999
    };

    WHEN("it is serialised and deserialised into a fresh object") {
      auto payload = serialiseToString(original);

      Test restored;
      REQUIRE(original != restored);
      deserialiseFromString(payload, restored);

      THEN("the restored object equals the original") {
        REQUIRE(restored == original);
      }
    }

    WHEN("it is serialised a second time after a round trip") {
      auto first = serialiseToString(original);

      Test restored;
      deserialiseFromString(first, restored);
      auto second = serialiseToString(restored);

      Test restoredAgain;
      deserialiseFromString(second, restoredAgain);

      THEN("the second round trip produces an equal object") {
        REQUIRE(restoredAgain == original);
        REQUIRE(restoredAgain == restored);
      }
    }
  }
}


SCENARIO("Deserialising twice into the same object does not accumulate data") {
  GIVEN("a populated object and its payload") {
    const Test source = Test{
      42,
      "populated",
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
      { {"alpha", 0.25f}, {"beta", -1.5f}, {"gamma", 100.0f} },
      { -5, 0, 7, 1000 },
      { {1, "one"}, {2, "two"}, {-3, "minus three"} },
      { Vector2{88,3}, 369 },
      999
    };

    auto payload = serialiseToString(source);

    Test target = Test{
      -777,
      "stale data that must disappear",
      {9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
      { {"alpha", 9.0f}, {"stale1", 1.0f}, {"stale2", 2.0f}, {"stale3", 3.0f} },
      { 7, 8, 9, 10, 11, 12 },
      { {1, "STALE"}, {50, "stale50"}, {51, "stale51"}, {52, "stale52"} },
      { Vector2{3,44}, 88 },
      -1
    };

    WHEN("the payload is deserialised twice") {
      deserialiseFromString(payload, target);
      deserialiseFromString(payload, target);

      THEN("the object still equals the source") {
        REQUIRE(target == source);
      }
    }
  }
}

SCENARIO("Empty containers serialise and deserialise correctly") {
  GIVEN("an object with empty containers and an empty string") {
    const Test empty = Test {};

    REQUIRE(empty.w.empty());
    REQUIRE(empty.u.empty());
    REQUIRE(empty.v.empty());
    REQUIRE(empty.y.empty());

    WHEN("it is serialised") {
      auto payload = serialiseToString(empty);

      THEN("each empty container is written as an empty array") {
        REQUIRE(countOccurrences(payload, "[]") == 4);
      }

      AND_WHEN("it is deserialised into a fresh object") {
        Test restored;
        deserialiseFromString(payload, restored);

        THEN("the containers are empty and the object equals the original") {
          REQUIRE(restored.w.empty());
          REQUIRE(restored.u.empty());
          REQUIRE(restored.v.empty());
          REQUIRE(restored.y.empty());
          REQUIRE(restored == empty);
        }
      }

      AND_WHEN("it is deserialised into an object full of data") {
        Test populated = Test{
          0,
          "hello",
          {},                                        // all zeros
          { {"hi", 0.5f}, {"yo", 1.3f} },
          { 69, 420 },
          { {67, "hihi"}, {1337, "bye"} },
          { Vector2{123,456}, 7 },
          555
        };

        deserialiseFromString(payload, populated);

        THEN("the existing container contents are cleared") {
          REQUIRE(populated.w.empty());
          REQUIRE(populated.u.empty());
          REQUIRE(populated.v.empty());
          REQUIRE(populated.y.empty());
          REQUIRE(populated == empty);
        }
      }
    }
  }
}