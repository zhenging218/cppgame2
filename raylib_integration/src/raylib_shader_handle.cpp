#include "engine.hpp"
#include "raylib_integration.hpp"

#include "raylib.h"
#include "external/glad.h"

namespace {
    using location_type = cppengine::RaylibShaderHandle::location_type;

    location_type getLocation(std::unordered_map<char const *, location_type> &shaderLocations, char const *name, ::Shader const &shader) {
        location_type location = -1;
        if (shaderLocations.contains(name)) {
            location = shaderLocations.at(name);
        } else {
            location = GetShaderLocation(shader, name);
            shaderLocations.insert({name, location});
        }

        return location;
    }

    void setShaderUniformValue(::Shader const &shader, location_type location, void const *value, int type) {
        if (location != -1) {
            SetShaderValue(shader, location, &value, type);
        }
    }

    void setShaderUniformValue(::Shader const &shader, location_type location, const std::uint32_t value) {
        if (location != -1) {
            glUniform1ui(location, value);
        }
    }

    void setShaderUniformValue(::Shader const &shader, location_type location, cppengine::Matrix2x2 const &value) {
        if (location != -1) {
            glUniformMatrix3fv(location, 1, GL_FALSE,
                cppengine::MathHelper::StructToArrayConverter<cppengine::Matrix2x2, float>::convert(value));
        }
    }

    void setShaderUniformValue(::Shader const &shader, location_type location, cppengine::Matrix3x3 const &value) {
        if (location != -1) {
            glUniformMatrix3fv(location, 1, GL_FALSE,
                cppengine::MathHelper::StructToArrayConverter<cppengine::Matrix3x3, float>::convert(value));
        }
    }

    void setShaderUniformValue(::Shader const &shader, location_type location, cppengine::Matrix4x4 const &value) {
        if (location != -1) {
            glUniformMatrix4fv(location, 1, GL_FALSE,
                cppengine::MathHelper::StructToArrayConverter<cppengine::Matrix4x4, float>::convert(value));
        }
    }
}

namespace cppengine {
    RaylibShaderHandle::RaylibShaderHandle(char const *name_, Shader shader_) : name(name_), shader(shader_) {

    }

    char const *RaylibShaderHandle::getName() const {
        return name;
    }

    void RaylibShaderHandle::bindShader() {
        ::BeginShaderMode(shader);
    }

    void RaylibShaderHandle::setUniform(char const *name, const std::int32_t value) {
        setShaderUniformValue(shader, getLocation(shaderLocations, name, shader), &value, ::SHADER_UNIFORM_INT);
    }

    void RaylibShaderHandle::setUniform(char const *name, const std::uint32_t value) {
        setShaderUniformValue(shader, getLocation(shaderLocations, name, shader), value);
    }

    void RaylibShaderHandle::setUniform(char const *name, const float value) {
        setShaderUniformValue(shader, getLocation(shaderLocations, name, shader), &value, ::SHADER_UNIFORM_FLOAT);
    }

    void RaylibShaderHandle::setUniform(char const *name, Colour const & value) {
        setShaderUniformValue(shader, getLocation(shaderLocations, name, shader),
            MathHelper::StructToArrayConverter<Colour, float>::convert(value), ::SHADER_UNIFORM_IVEC4);
    }

    void RaylibShaderHandle::setUniform(char const *name, Vector2 const & value) {
        setShaderUniformValue(shader, getLocation(shaderLocations, name, shader),
            MathHelper::StructToArrayConverter<Vector2, float>::convert(value), ::SHADER_UNIFORM_IVEC2);
    }

    void RaylibShaderHandle::setUniform(char const *name, Vector3 const & value) {
        setShaderUniformValue(shader, getLocation(shaderLocations, name, shader),
            MathHelper::StructToArrayConverter<Vector3, float>::convert(value), ::SHADER_UNIFORM_IVEC3);
    }
    void RaylibShaderHandle::setUniform(char const *name, Vector4 const & value) {
        setShaderUniformValue(shader, getLocation(shaderLocations, name, shader),
            MathHelper::StructToArrayConverter<Vector4, float>::convert(value), ::SHADER_UNIFORM_IVEC4);
    }

    void RaylibShaderHandle::setUniform(char const *name, Matrix2x2 const & value) {
        setShaderUniformValue(shader, getLocation(shaderLocations, name, shader), value);
    }

    void RaylibShaderHandle::setUniform(char const *name, Matrix3x3 const & value) {
        setShaderUniformValue(shader, getLocation(shaderLocations, name, shader), value);
    }

    void RaylibShaderHandle::setUniform(char const *name, Matrix4x4 const & value) {
        setShaderUniformValue(shader, getLocation(shaderLocations, name, shader), value);
    }

    void RaylibShaderHandle::setUniform(char const *name, ObjectHandle<TextureHandle> value) {

    }

    void RaylibShaderHandle::unbindShader() {
        ::EndShaderMode();
    }

    RaylibShaderHandle::~RaylibShaderHandle() {
        ::UnloadShader(shader);
    }
}
