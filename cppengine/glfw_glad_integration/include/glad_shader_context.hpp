#ifndef GLAD_SHADER_CONTEXT_HPP
#define GLAD_SHADER_CONTEXT_HPP
#include <unordered_map>

#include "glad_shader_helper.hpp"
#include "graphics/shader_context.hpp"

namespace cppengine {
    class GladShaderContext : public ShaderContext {
    private:
        std::unordered_map<std::string, ObjectHandle<ShaderHandle>, GladRendererHelper::StringHash, std::equal_to<>> shaders;

    public:
        GladShaderContext();
        GladShaderContext(GladShaderContext const &) = delete;
        GladShaderContext &operator=(GladShaderContext const &) = delete;

        ShaderID loadShader(std::string_view shaderName) override;
        ObjectHandle<ShaderHandle> getShader(std::string_view shaderName) override;

        ~GladShaderContext() override;
    };

    inline GladShaderContext::~GladShaderContext() = default;
}

#endif
