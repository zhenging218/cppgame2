#include <filesystem>

#include "engine.hpp"
#include "gg_integration.hpp"

namespace {
    using namespace cppengine;

    int getLocation(std::unordered_map<std::string, int> &locations, std::string const &name, int program) {
        auto [it, inserted] = locations.try_emplace(name, -1);

        if (inserted) {
            it->second = glGetUniformLocation(program, name.c_str());
        }

        return it->second;
    }

    std::pair<std::string, std::string> getShaderSourcePaths(std::string const &name) {
        struct Adapter : ShaderContext {
            ~Adapter() override = 0;

            static std::pair<std::string, std::string> getShaderPaths(std::string const &name) {
                return getShaderSourcePaths(name);
            }
        };

        return Adapter::getShaderPaths(name);
    }
}

namespace cppengine {
    GladShaderHandle::GladShaderHandle(std::string const &name_) : name(name_), id() {
    }

    GladShaderHandle::GladShaderHandle(std::string &&name_) : name(std::move(name_)), id() {
        
    }

    GladShaderHandle::~GladShaderHandle() {
        glDeleteProgram(id);
    }

    void GladShaderHandle::bindShader() {
        glUseProgram(id);
    }

    const std::string &GladShaderHandle::getName() const {
        return name;
    }
    
    void GladShaderHandle::setUniform(const std::string &name, const std::int32_t value) {
        int location = getLocation(locations, name, id);

        if (location != -1) {
            glProgramUniform1i(id, location, value);
        }
    }

    void GladShaderHandle::setUniform(const std::string &name, const std::uint32_t value) {
        int location = getLocation(locations, name, id);

        if (location != -1) {
            glProgramUniform1ui(id, location, value);
        }
    }

    void GladShaderHandle::setUniform(const std::string &name, const float value) {
        int location = getLocation(locations, name, id);

        if (location != -1) {
            glProgramUniform1f(id, location, value);
        }
    }

    void GladShaderHandle::setUniform(const std::string &name, const Colour &value) {
        int location = getLocation(locations, name, id);

        if (location != -1) {
            glProgramUniform3fv(id, location, 1,
                MathHelper::StructToArrayConverter<Colour, float>::convert(value));
        }
    }

    void GladShaderHandle::setUniform(const std::string &name, const Vector2 &value) {
        int location = getLocation(locations, name, id);

        if (location != -1) {
            glProgramUniform2fv(id, location, 1,
                MathHelper::StructToArrayConverter<Vector2, float>::convert(value));
        }
    }

    void GladShaderHandle::setUniform(const std::string &name, const Vector3 &value) {
        int location = getLocation(locations, name, id);

        if (location != -1) {
            glProgramUniform3fv(id, location, 1,
                MathHelper::StructToArrayConverter<Vector3, float>::convert(value));
        }
    }

    void GladShaderHandle::setUniform(const std::string &name, const Vector4 &value) {
        int location = getLocation(locations, name, id);

        if (location != -1) {
            glProgramUniform4fv(id, location, 1,
                MathHelper::StructToArrayConverter<Vector4, float>::convert(value));
        }
    }

    void GladShaderHandle::setUniform(const std::string &name, const Matrix2x2 &value) {
        int location = getLocation(locations, name, id);

        if (location != -1) {
            glUniformMatrix2fv(id, location, GL_TRUE,
                MathHelper::StructToArrayConverter<Matrix2x2, float>::convert(value));
        }
    }

    void GladShaderHandle::setUniform(const std::string &name, const Matrix3x3 &value) {
        int location = getLocation(locations, name, id);

        if (location != -1) {
            glUniformMatrix3fv(id, location, GL_TRUE,
                MathHelper::StructToArrayConverter<Matrix3x3, float>::convert(value));
        }
    }

    void GladShaderHandle::setUniform(const std::string &name, const Matrix4x4 &value) {
        int location = getLocation(locations, name, id);

        if (location != -1) {
            glUniformMatrix4fv(id, location, GL_TRUE,
                MathHelper::StructToArrayConverter<Matrix4x4, float>::convert(value));
        }
    }

    void GladShaderHandle::setUniform(const std::string &name, ObjectHandle<TextureHandle> value) {}

    void GladShaderHandle::unbindShader() {
        glUseProgram(0);
    }
}
