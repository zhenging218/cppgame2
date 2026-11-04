#include "engine.hpp"

namespace cppengine {
    Material::Material() : shaderName(DEFAULT_SHADER_NAME) {

    }

    std::unordered_map<std::string, Uniform> const &Material::getUniforms() const {
        return uniforms;
    }

    void Material::setShader(std::string const &name) {
        shaderName = name;
    }

    std::string_view Material::getShaderName() const {
        return shaderName;
    }
}
