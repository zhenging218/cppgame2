#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <map>

#include "ecs/component.hpp"

namespace cppengine {
    class Material : public Component {
        std::map<char const *, Uniform> uniforms;
    };
}

#endif
