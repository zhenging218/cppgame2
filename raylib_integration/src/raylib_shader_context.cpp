#include "raylib_shader_context.hpp"

#include <cstring>

#include "engine.hpp"
#include "raylib_integration.hpp"

namespace {
    constexpr char default_shader_name[] = "defaultShader";
}

namespace cppengine {
    RaylibShaderContext::RaylibShaderContext() {
        auto defaultShader = LoadShader(0, 0);
        shaders.insert({ShaderID::DEFAULT_DIFFUSE_SHADER,
            static_handle_cast<ShaderHandle>(
                createHandle<RaylibShaderHandle>(default_shader_name, defaultShader))});
    }

    ObjectHandle<ShaderHandle> RaylibShaderContext::getShader(ShaderID shaderId) {
        if (shaders.contains(shaderId)) {
            return shaders.at(shaderId);
        }
        return nullptr;
    }

    ShaderID RaylibShaderContext::loadShader(std::string const &shaderName) {
        auto result = std::ranges::find_if(shaders, [&](auto const &shader) {
            return shader.second->getName() == shaderName;
        });

        if (result != shaders.end()) {
            return result->first;
        }

        auto [vertexShaderPath, fragmentShaderPath] = getShaderSourcePaths(shaderName);

        auto handle = createHandle<RaylibShaderHandle>(shaderName,
            LoadShader(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));

        if (handle->getMaterial().shader.id == 0) {
            return NO_SHADER;
        }

        auto [it, inserted] = shaders.insert(
            {
                static_cast<ShaderID>(HashHelper::fnv1a_64(std::string_view{shaderName})),
                static_handle_cast<ShaderHandle>(handle)
                });

        if (inserted) {
            return it->first;
        }

        return NO_SHADER;
    }
}
