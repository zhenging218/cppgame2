#ifndef ENUM_MODEL_ID_HPP
#define ENUM_MODEL_ID_HPP
#include <cstdint>

#include "hash_helper.hpp"

namespace cppengine {
    enum ModelID : std::uint64_t {
        NO_MODEL = 0,
        TRIANGLE = HashHelper::fnv1a_64("TRIANGLE"),
        BOX2D = HashHelper::fnv1a_64("BOX2D")
    };
}

#endif