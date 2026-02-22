#ifndef RAYLIB_SHADER_CONTEXT_HPP
#define RAYLIB_SHADER_CONTEXT_HPP
#include "../../cmake-build-release/_deps/raylib-src/src/raylib.h"
#include "graphics/shader_context.hpp"

namespace cppengine {
    class RaylibShaderContext : public ShaderContext {
    private:
        std::unordered_map<ShaderID, ObjectHandle<ShaderHandle>> shaders;

    public:

        RaylibShaderContext();
        ShaderID loadShader(std::string const & shaderName) override;
        ObjectHandle<ShaderHandle> getShader(ShaderID shaderId) override;

    };
}

#endif
