#ifndef SHADER_HANDLE_HPP
#define SHADER_HANDLE_HPP
#include <cstdint>

namespace cppengine {
    class ShaderHandle {
    private:

    public:

        virtual std::uint64_t getId() const = 0;

        virtual void bindShader() = 0;

        virtual void setUniform(char const *name, const std::uint32_t value);
        virtual void setUniform(char const *name, const std::int32_t value);
        virtual void setUniform(char const *name, const std::uint64_t value);
        virtual void setUniform(char const *name, const std::int64_t value);
        virtual void setUniform(char const *name, const float value);
        virtual void setUniform(char const *name, const double value);
        virtual void setUniform(char const *name, Colour const & value);
        virtual void setUniform(char const *name, Vector2 const & value);
        virtual void setUniform(char const *name, Vector3 const & value);
        virtual void setUniform(char const *name, Vector4 const & value);
        virtual void setUniform(char const *name, Matrix2x2 const & value);
        virtual void setUniform(char const *name, Matrix3x3 const & value);
        virtual void setUniform(char const *name, Matrix4x4 const & value);
        virtual void setUniform(char const *name, TextureHandle const & value);

        virtual void unbindShader() = 0;

        virtual ~ShaderHandle() = 0;
    };

    inline ShaderHandle::~ShaderHandle() = default;
}

#endif