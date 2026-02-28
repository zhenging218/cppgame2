#include <filesystem>

#include "engine.hpp"
#include "gg_integration.hpp"

namespace {
    using namespace cppengine;

    const std::unordered_map<std::string, std::string> defaultLocationNames = {
        { ShaderLocation::SHADER_MVP_MATRIX_UNIFORM, "mvp" },
        { ShaderLocation::SHADER_DIFFUSE_COLOUR_UNIFORM, "tint" },
        { ShaderLocation::SHADER_DIFFUSE_TEXTURE_UNIFORM, "albedo" },
    };

    std::string const &getDefaultUniformLocationName(std::string const &name) {
        auto result = std::ranges::find_if(defaultLocationNames, [&name](auto const &location) {
           return name == location.first;
        });

        return result != defaultLocationNames.end() ? result->second : name;
    }

    int getLocation(std::unordered_map<std::string, int> &locations, std::string const &name, GLuint program) {
        auto [it, inserted] = locations.try_emplace(getDefaultUniformLocationName(name), -1);

        if (inserted) {
            it->second = glGetUniformLocation(program, name.c_str());
        }

        return it->second;
    }

    GLuint loadShader(char const *vertPath, char const *fragPath) {
        std::string vertSource;
        std::string fragSource;

        {
            auto vertFile = Assets::openFile(vertPath);
            vertSource = {std::istreambuf_iterator<char>(vertFile), std::istreambuf_iterator<char>()};
        }
        {
            auto fragFile = Assets::openFile(fragPath);
            fragSource = {std::istreambuf_iterator<char>(fragFile), std::istreambuf_iterator<char>()};
        }

        return GladShaderHelper::compileShader(vertPath, fragPath,
            vertSource.c_str(), fragSource.c_str());
    }

    GLuint createShaderProgram(std::string const & name) {
        auto const &[vert, frag] = ShaderHelper::getShaderSourcePaths(name);
        return loadShader(vert.c_str(), frag.c_str());
    }
}

namespace cppengine {
    GladShaderHandle::GladShaderHandle(std::string const &name_, GLuint id_) : shaderName(name_), id(id_) {

    }

    GladShaderHandle::GladShaderHandle(std::string &&name_, GLuint id_) : shaderName(std::move(name_)), id(id_) {

    }

    GladShaderHandle::GladShaderHandle(std::string const &name_) : id(createShaderProgram(name_)), shaderName(name_) {

    }

    GladShaderHandle::GladShaderHandle(std::string &&name_) : id(createShaderProgram(name_)), shaderName(std::move(name_)) {
        
    }

    GladShaderHandle::~GladShaderHandle() {
        glDeleteProgram(id);
    }

    void GladShaderHandle::bindShader() {
        glUseProgram(id);
    }

    const std::string &GladShaderHandle::getName() const {
        return shaderName;
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
            glProgramUniform4fv(id, location, 1,
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
            glProgramUniformMatrix2fv(id, location, 1, GL_TRUE,
                MathHelper::StructToArrayConverter<Matrix2x2, float>::convert(value));
        }
    }

    void GladShaderHandle::setUniform(const std::string &name, const Matrix3x3 &value) {
        int location = getLocation(locations, name, id);

        if (location != -1) {
            glProgramUniformMatrix3fv(id, location, 1, GL_TRUE,
                MathHelper::StructToArrayConverter<Matrix3x3, float>::convert(value));
        }
    }

    void GladShaderHandle::setUniform(const std::string &name, const Matrix4x4 &value) {
        int location = getLocation(locations, name, id);

        if (location != -1) {
            glProgramUniformMatrix4fv(id, location, 1, GL_TRUE,
                MathHelper::StructToArrayConverter<Matrix4x4, float>::convert(value));
        }
    }

    void GladShaderHandle::setUniform(const std::string &name, ObjectHandle<TextureHandle> value) {
        int location = getLocation(locations, name, id);

        if (location != -1) {
            glProgramUniform1i(id, location, static_handle_cast<GladTextureHandle>(value)->getId());
        }
    }

    void GladShaderHandle::unbindShader() {
        glUseProgram(0);
    }

    GLuint GladShaderHandle::getId() const {
        return id;
    }
}
