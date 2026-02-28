#include "engine.hpp"
#include "gg_integration.hpp"

namespace {
    using namespace cppengine;

    constexpr char const DEFAULT_VERTEX_SHADER_SOURCE[] = R"(
        #version 330 core

        layout(location = 0) in vec3 position;
        layout(location = 1) in vec3 normal;
        layout(location = 2) in vec3 tangent;
        layout(location = 3) in vec4 colour;
        layout(location = 4) in vec2 uv;

        uniform mat4 mvp;

        out vec4 vertColour;
        // out vec2 vertUV;

        void main() {
            gl_Position = mvp * vec4(position, 1.0);
            vertColour = colour;
            // vertUV = uv;
        }
    )";

    constexpr char const DEFAULT_FRAGMENT_SHADER_SOURCE[] = R"(
        #version 330 core

        in vec4 vertColour;
        // in vec2 vertUV;

        uniform sampler2D albedo;
        uniform vec4 tint;

        out vec4 fragment;

        void main() {
            // fragment = texture(albedo, vertUV) * vertColour * tint;
            fragment = vertColour * tint;
        }
    )";

    GLuint loadDefaultShader() {
        return GladShaderHelper::compileShader(
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

    ShaderID GladShaderContext::getShader(std::string const &shaderName) const {
        auto result = std::ranges::find_if(shaders, [&shaderName] (auto const &shader) {
            return shader.second->getName() == shaderName;
        });

        if (result != shaders.end()) {
            return result->first;
        }

        return NO_SHADER;
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
