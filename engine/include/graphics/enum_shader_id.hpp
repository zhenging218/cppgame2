#ifndef ENUM_SHADER_ID_HPP
#define ENUM_SHADER_ID_HPP
#include <cstdint>

#include "hash_helper.hpp"

namespace cppengine {
    constexpr char default_shader_name[] = "DEFAULT_DIFFUSE_SHADER";

    enum ShaderID : std::uint64_t {
        NO_SHADER = 0,
        DEFAULT_DIFFUSE_SHADER = HashHelper::fnv1a_64(default_shader_name)
    };
}

#endif