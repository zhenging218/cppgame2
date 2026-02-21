#ifndef ENUM_SHADER_ID_HPP
#define ENUM_SHADER_ID_HPP
#include <cstdint>

#include "hash_helper.hpp"

namespace cppengine {
    enum ShaderID : std::uint64_t {
        NO_SHADER = 0,
        DEFAULT_DIFFUSE_SHADER = HashHelper::fnv1a_64("DEFAULT_DIFFUSE_SHADER")
    };
}

#endif