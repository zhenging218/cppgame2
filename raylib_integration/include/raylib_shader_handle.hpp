#ifndef RAYLIB_SHADER_HANDLE_HPP
#define RAYLIB_SHADER_HANDLE_HPP

#include <unordered_map>

#include "raylib.h"
#include "graphics/shader_handle.hpp"
#include "graphics/texture_handle.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {
    class RaylibShaderHandle : public ShaderHandle {
    public:
        using location_type = std::remove_reference_t<decltype(std::declval<::Shader>().locs[0])>;

    private:
        std::string shaderName;
        ::Material material;
        std::unordered_map<std::string, location_type> shaderLocations;

    public:
        RaylibShaderHandle(std::string const &name_, ::Shader shader_);
        RaylibShaderHandle(std::string &&name_, ::Shader shader_);
        RaylibShaderHandle(RaylibShaderHandle const &) = delete;
        RaylibShaderHandle &operator=(RaylibShaderHandle const &) = delete;

        RaylibShaderHandle(RaylibShaderHandle &&other) noexcept;
        RaylibShaderHandle &operator=(RaylibShaderHandle &&other) noexcept;

        std::string const &getName() const override;

        void bindShader() override;
        void setUniform(std::string const &name, const std::int32_t value) override;
        void setUniform(std::string const &name, const std::uint32_t value) override;
        void setUniform(std::string const &name, const float value) override;
        void setUniform(std::string const &name, Colour const & value) override;
        void setUniform(std::string const &name, Vector2 const & value) override;
        void setUniform(std::string const &name, Vector3 const & value) override;
        void setUniform(std::string const &name, Vector4 const & value) override;
        void setUniform(std::string const &name, Matrix2x2 const & value) override;
        void setUniform(std::string const &name, Matrix3x3 const & value) override;
        void setUniform(std::string const &name, Matrix4x4 const & value) override;
        void setUniform(std::string const &name, ObjectHandle<TextureHandle> value) override;
        void unbindShader() override;

        ::Material const &getMaterial() const;

        ~RaylibShaderHandle() override;
    };
}

#endif