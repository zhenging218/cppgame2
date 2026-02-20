#ifndef ENUM_MODEL_ID_HPP
#define ENUM_MODEL_ID_HPP
#include <cstdint>

namespace cppengine {
    enum ModelID : std::uint64_t {
        NO_MODEL = 0,
        TRIANGLE = 1,
        BOX2D = 2
    };
}

#endif