#include "engine.hpp"
#include "gg_integration.hpp"

namespace {
    using namespace cppengine;

    constexpr char const DEFAULT_VERTEX_SHADER_SOURCE[] = "";
    constexpr char const DEFAULT_FRAGMENT_SHADER_SOURCE[] = "";

    GLuint loadDefaultShader() {
        return cppengine::GladShaderHelper::compileShader(
            DEFAULT_SHADER_NAME,
            DEFAULT_SHADER_NAME,
            DEFAULT_VERTEX_SHADER_SOURCE,
            DEFAULT_FRAGMENT_SHADER_SOURCE);
    }
}

namespace cppengine {
    GladShaderContext::GladShaderContext() : shaders({
        {
            ShaderID::DEFAULT_DIFFUSE_SHADER,
            ObjectHandle(new GladShaderHandle(DEFAULT_SHADER_NAME, loadDefaultShader()))
        }
    }) {

    }

    ObjectHandle<ShaderHandle> GladShaderContext::getShader(ShaderID shaderId) {
        auto result = std::ranges::find_if(shaders, [&shaderId] (auto const &shader) {
            return shader.first == shaderId;
        });

        if (result != shaders.end()) {
            return result->second;
        }

        return nullptr;
    }

    ShaderID GladShaderContext::loadShader(const std::string &shaderName) {
        auto result = std::ranges::find_if(shaders, [&shaderName] (auto const &shader) {
            return shader.second->getName() == shaderName;
        });

        if (result != shaders.end()) {
            return result->first;
        }

        ObjectHandle<ShaderHandle> shader = new GladShaderHandle(shaderName);
        auto const [it, inserted] = shaders.try_emplace(static_cast<ShaderID>(static_handle_cast<GladShaderHandle>(shader)->getId()), shader);

        if (inserted) {
            return it->first;
        }

        return ShaderID::NO_SHADER;
    }
}
