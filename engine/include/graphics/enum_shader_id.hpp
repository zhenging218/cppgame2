#ifndef ENUM_SHADER_ID_HPP
#define ENUM_SHADER_ID_HPP
#include <cstdint>

namespace cppengine {
    enum ShaderID : std::uint64_t {
        NO_SHADER = 0,
        DEFAULT_DIFFUSE_SHADER = 1
    };
}

#endif