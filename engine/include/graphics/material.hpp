#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <map>

#include "ecs/component.hpp"

namespace cppengine {
    class Material : public Component {
        std::uint64_t shaderId;
        std::unordered_map<char const *, Uniform> uniforms;
        std::unordered_map<char const *, Texture> textures;

    public:
    };
}

#endif
