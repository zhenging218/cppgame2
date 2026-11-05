#include "engine.hpp"
#include "gg_integration.hpp"

namespace {
    using namespace cppengine;

    constexpr char const DEFAULT_VERTEX_SHADER_SOURCE[] = R"(#version 330 core

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

    constexpr char const DEFAULT_FRAGMENT_SHADER_SOURCE[] = R"(#version 330 core

        in vec4 vertColour;
        // in vec2 vertUV;

        uniform sampler2D albedo;
        uniform vec4 tint;

        out vec4 fragment;

        void main() {
            // fragment = texture(albedo, vertUV) * vertColour * tint;
            fragment = vertColour * tint;
            // fragment = vec4(1,1,1,1);
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
    GladShaderContext::GladShaderContext() {
        shaders = {
            {
                DEFAULT_SHADER_NAME,
                ObjectHandle(new GladShaderHandle(loadDefaultShader()))
            }
        };
    }

    ObjectHandle<ShaderHandle> GladShaderContext::getShader(std::string_view shaderName) {
        auto result = shaders.find(shaderName);

        if (result != shaders.end()) {
            return result->second;
        }

        return nullptr;
    }

    ShaderID GladShaderContext::loadShader(std::string_view shaderName) {
        auto result = shaders.find(shaderName);

        if (result != shaders.end()) {
            return result->second->getId();
        }

        // todo: try to load and compile the shader from assets

        // only register the shader if load and compile succeeds
        // i.e. only create the shader handle upon success then do shaders.emplace
        // otherwise, return no shader

        /*
        ObjectHandle<ShaderHandle> shader = new GladShaderHandle(shaderName);
        auto const [it, inserted] = shaders.try_emplace(static_cast<ShaderID>(static_handle_cast<GladShaderHandle>(shader)->getId()), shader);

        if (inserted) {
            return it->first;
        }
        */

        return ShaderID::NO_SHADER;
    }
}
