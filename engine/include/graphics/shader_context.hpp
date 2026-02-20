#ifndef SHADER_CONTEXT_HPP
#define SHADER_CONTEXT_HPP
#include "enum_shader_id.hpp"
#include "shader_handle.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {
    class ShaderContext {
    private:

    public:

        virtual ShaderID loadShader(char const *shaderName, char const *vertexShaderPath, char const *fragmentShaderPath) = 0;
        virtual ObjectHandle<ShaderHandle> getShader(ShaderID shaderId) = 0;

        virtual ~ShaderContext() = 0;
    };

    inline ShaderContext::~ShaderContext() = default;
}

#endif