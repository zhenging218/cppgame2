#ifndef GLAD_SHADER_HANDLE_HPP
#define GLAD_SHADER_HANDLE_HPP
#include <unordered_map>

#include <string>
#include "graphics/shader_handle.hpp"

namespace cppengine {
    class GladShaderHandle : public ShaderHandle {
    private:

        GLuint id;
        std::unordered_map<std::string, int> locations;

        friend class GladShaderContext;
    public:
        explicit GladShaderHandle(GLuint id_);
        explicit GladShaderHandle(std::string_view name_);

        GladShaderHandle(GladShaderHandle const &) = delete;
        GladShaderHandle &operator=(GladShaderHandle const &) = delete;

        void bindShader() override;

        void setUniform(const std::string &name, const std::int32_t value) override;

        void setUniform(const std::string &name, const std::uint32_t value) override;

        void setUniform(const std::string &name, const float value) override;

        void setUniform(const std::string &name, const Colour &value) override;

        void setUniform(const std::string &name, const Vector2 &value) override;

        void setUniform(const std::string &name, const Vector3 &value) override;

        void setUniform(const std::string &name, const Vector4 &value) override;

        void setUniform(const std::string &name, const Matrix2x2 &value) override;

        void setUniform(const std::string &name, const Matrix3x3 &value) override;

        void setUniform(const std::string &name, const Matrix4x4 &value) override;

        void setUniform(const std::string &name, ObjectHandle<TextureHandle> value) override;

        void unbindShader() override;

        ~GladShaderHandle() override;

        ShaderID getId() const override;
    };
}

#endif
