#ifndef GLAD_SHADER_CONTEXT_HPP
#define GLAD_SHADER_CONTEXT_HPP
#include <unordered_map>

#include "graphics/shader_context.hpp"

namespace cppengine {
    class GladShaderContext : public ShaderContext {
    private:
        ObjectAllocator<GladShaderHandle> allocator;
        std::unordered_map<ShaderID, ObjectHandle<ShaderHandle>> shaders;

    public:
        GladShaderContext();
        GladShaderContext(GladShaderContext const &) = delete;
        GladShaderContext &operator=(GladShaderContext const &) = delete;

        ShaderID loadShader(const std::string &shaderName) override;

        ShaderID getShader(std::string const &shaderName) const override;
        ObjectHandle<ShaderHandle> getShader(ShaderID shaderId) override;

        ~GladShaderContext() override;
    };

    inline GladShaderContext::~GladShaderContext() = default;
}

#endif
