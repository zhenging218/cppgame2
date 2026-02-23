#ifndef GLAD_SHADER_CONTEXT_HPP
#define GLAD_SHADER_CONTEXT_HPP
#include <unordered_map>

#include "graphics/shader_context.hpp"

namespace cppengine {
    class GladShaderContext : public ShaderContext {
    private:
        std::unordered_map<ShaderID, ObjectHandle<ShaderHandle>> shaders;

    public:
        ShaderID loadShader(const std::string &shaderName) override;

        ObjectHandle<ShaderHandle> getShader(ShaderID shaderId) override;

        ~GladShaderContext() override;
    };
}

#endif
