#include "raylib_shader_context.hpp"

#include "engine.hpp"
#include "raylib_integration.hpp"

namespace cppengine {
    ObjectHandle<ShaderHandle> RaylibShaderContext::getShader(ShaderID shaderId) {
        return nullptr;
    }

    ShaderID RaylibShaderContext::loadShader(char const *shaderName, char const *vertexShaderPath, char const *fragmentShaderPath) {
        return NO_SHADER;
    }
}
