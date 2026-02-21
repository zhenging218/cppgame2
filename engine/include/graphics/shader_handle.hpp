#ifndef SHADER_HANDLE_HPP
#define SHADER_HANDLE_HPP
#include <cstdint>

#include "memory/object_handle.hpp"
#include "texture_handle.hpp"

namespace cppengine {
    struct Colour;
    class Vector2;
    class Vector3;
    class Vector4;
    class Matrix2x2;
    class Matrix3x3;
    class Matrix4x4;

    class ShaderHandle {
    private:

    public:
        virtual std::string const &getName() const = 0;

        virtual void bindShader() = 0;

        virtual void setUniform(char const *name, const std::int32_t value) = 0;
        virtual void setUniform(char const *name, const std::uint32_t value) = 0;
        virtual void setUniform(char const *name, const float value) = 0;
        virtual void setUniform(char const *name, Colour const & value) = 0;
        virtual void setUniform(char const *name, Vector2 const & value) = 0;
        virtual void setUniform(char const *name, Vector3 const & value) = 0;
        virtual void setUniform(char const *name, Vector4 const & value) = 0;
        virtual void setUniform(char const *name, Matrix2x2 const & value) = 0;
        virtual void setUniform(char const *name, Matrix3x3 const & value) = 0;
        virtual void setUniform(char const *name, Matrix4x4 const & value) = 0;
        virtual void setUniform(char const *name, ObjectHandle<TextureHandle> value) = 0;

        virtual void unbindShader() = 0;

        virtual ~ShaderHandle() = 0;
    };

    inline ShaderHandle::~ShaderHandle() = default;
}

#endif