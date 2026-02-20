#ifndef RAYLIB_SHADER_HANDLE_HPP
#define RAYLIB_SHADER_HANDLE_HPP

#include <unordered_map>

#include "raylib.h"
#include "graphics/shader_handle.hpp"
#include "graphics/texture_handle.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {
    class RaylibShaderHandle : ShaderHandle {
    public:
        using location_type = std::remove_reference_t<decltype(std::declval<::Shader>().locs[0])>;

    private:


        ::Shader shader;
        std::unordered_map<char const *, location_type> shaderLocations;

    public:
        RaylibShaderHandle(::Shader shader_);
        RaylibShaderHandle(RaylibShaderHandle const &) = delete;
        RaylibShaderHandle &operator=(RaylibShaderHandle const &) = delete;

        void bindShader() override;
        void setUniform(char const *name, const std::int32_t value) override;
        void setUniform(char const *name, const float value) override;
        void setUniform(char const *name, Colour const & value) override;
        void setUniform(char const *name, Vector2 const & value) override;
        void setUniform(char const *name, Vector3 const & value) override;
        void setUniform(char const *name, Vector4 const & value) override;
        void setUniform(char const *name, Matrix2x2 const & value) override;
        void setUniform(char const *name, Matrix3x3 const & value) override;
        void setUniform(char const *name, Matrix4x4 const & value) override;
        void setUniform(char const *name, ObjectHandle<TextureHandle> value) override;
        void unbindShader() override;

        ~RaylibShaderHandle() override;
    };
}

#endif