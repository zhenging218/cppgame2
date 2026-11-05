#ifndef ENUM_MODEL_ID_HPP
#define ENUM_MODEL_ID_HPP
#include <cstdint>

#include "hash_helper.hpp"

namespace cppengine {
    constexpr char TRIANGLE_PRIMITIVE_NAME[] = "TRIANGLE";
    constexpr char BOX2D_PRIMITIVE_NAME[] = "TRIANGLE";

    enum ModelID : std::uint64_t {
        NO_MODEL = 0,
        TRIANGLE = HashHelper::fnv1a_64(TRIANGLE_PRIMITIVE_NAME),
        BOX2D = HashHelper::fnv1a_64(BOX2D_PRIMITIVE_NAME)
    };
}

#endif