#include "raylib_shader_context.hpp"

#include <cstring>

#include "engine.hpp"
#include "raylib_integration.hpp"

namespace {
    constexpr char default_shader_name[] = "defaultShader";

    constexpr cppengine::ShaderID fnv1a_64(std::string_view str) {
        uint64_t hash = 14695981039346656037ULL;
        for (char c : str) {
            hash ^= static_cast<uint64_t>(c);
            hash *= 1099511628211ULL;
        }
        return static_cast<cppengine::ShaderID>(hash);
    }
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

    ShaderID RaylibShaderContext::loadShader(char const *shaderName, char const *vertexShaderPath, char const *fragmentShaderPath) {
        auto result = std::ranges::find_if(shaders, [&](auto const &shader) {
            return shader.second->getName() == shaderName;
        });

        if (result != shaders.end()) {
            return result->first;
        }

        auto shader = LoadShader(vertexShaderPath, fragmentShaderPath);
        auto [it, inserted] = shaders.insert(
            {fnv1a_64(std::string_view{shaderName}), static_handle_cast<ShaderHandle>(
                createHandle<RaylibShaderHandle>(shaderName, shader))});

        if (inserted) {
            return it->first;
        }

        return NO_SHADER;
    }
}
