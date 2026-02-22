#ifndef SHADER_CONTEXT_HPP
#define SHADER_CONTEXT_HPP
#include "enum_shader_id.hpp"
#include "shader_handle.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {
    class ShaderContext {
    private:

    protected:
        std::pair<std::string, std::string> getShaderSourcePaths(std::string const &name) const;

    public:

        virtual ShaderID loadShader(std::string const &shaderName) = 0;
        virtual ObjectHandle<ShaderHandle> getShader(ShaderID shaderId) = 0;

        virtual ~ShaderContext() = 0;
    };

    inline ShaderContext::~ShaderContext() = default;
}

#endif