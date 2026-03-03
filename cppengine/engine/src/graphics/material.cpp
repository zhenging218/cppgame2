#include "engine.hpp"

namespace cppengine {
    Material::Material() : shaderId(NO_SHADER) {

    }

    ShaderID Material::getShaderId() const {
        return shaderId;
    }

    std::unordered_map<std::string, Uniform> const &Material::getUniforms() const {
        return uniforms;
    }

    void Material::setShader(std::string const &name) {
        shaderId = Renderer::loadShader(name);
    }
}
