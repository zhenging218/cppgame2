#include <cstring>

#include "engine.hpp"
#include "raylib_integration.hpp"

#include "raylib.h"
#include "external/glad.h"

namespace {
    using location_type = cppengine::RaylibShaderHandle::location_type;
    using material_attribute_index_type = int;

    material_attribute_index_type getDefaultMaterialLocation(std::string const &name) {
        static const std::unordered_map<std::string, material_attribute_index_type> defaultLocations = {
            {cppengine::SHADER_DIFFUSE_COLOUR_UNIFORM, MATERIAL_MAP_DIFFUSE},
            {cppengine::SHADER_DIFFUSE_TEXTURE_UNIFORM, MATERIAL_MAP_DIFFUSE}
        };

        auto result = defaultLocations.find(name);
        if (result != defaultLocations.end()) {
            return result->second;
        }

        return -1;
    }

    location_type getLocation(std::unordered_map<std::string, location_type> &shaderLocations, std::string const &name, ::Shader const &shader) {

        auto [it, inserted] = shaderLocations.try_emplace(name, -1);

        if (inserted) {
            it->second = GetShaderLocation(shader, name.c_str());
        }

        return it->second;
    }

    void setShaderUniformValue(::Shader const &shader, location_type location, void const *value, int type) {
        if (location != -1) {
            SetShaderValue(shader, location, value, type);
        }
    }

    void setShaderUniformValue(::Shader const &shader, location_type location, const std::uint32_t value) {
        if (location != -1) {
            glUniform1ui(location, value);
        }
    }

    void setShaderUniformValue(::Shader const &shader, location_type location, cppengine::Matrix2x2 const &value) {
        if (location != -1) {
            glUniformMatrix2fv(location, 1, GL_FALSE,
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

    void setShaderUniformValue(::Shader const &shader, location_type location, ::Texture2D const &texture) {
        if (location != -1) {
            SetShaderValueTexture(shader, location, texture);
        }
    }

    ::Material createMaterial(::Shader const &shader) {
        ::Material material = LoadMaterialDefault();
        material.shader = shader;
        return material;
    }

    ::Material moveMaterial(::Material &&material) {
        ::Material result = {};
        std::swap(result.shader, material.shader);
        std::swap(result.maps, material.maps);
        std::memcpy(result.params, material.params, sizeof(float) * 4);
        std::memset(material.params, 0, sizeof(float) * 4);
        return result;
    }
}

namespace cppengine {
    RaylibShaderHandle::RaylibShaderHandle(std::string const &name_, Shader shader_) : shaderName(name_), material(createMaterial(shader_)) {

    }

    RaylibShaderHandle::RaylibShaderHandle(std::string &&name_, Shader shader_) : shaderName(name_), material(createMaterial(shader_)) {

    }

    RaylibShaderHandle::RaylibShaderHandle(RaylibShaderHandle &&other) noexcept
        : shaderName(std::move(other.shaderName)), shaderLocations(std::move(other.shaderLocations)), material(moveMaterial(std::move(other.material))) {

    }

    RaylibShaderHandle &RaylibShaderHandle::operator=(RaylibShaderHandle &&other) noexcept {
        std::swap(other.shaderLocations, shaderLocations);
        std::swap(other.material, material);
        std::swap(other.shaderName, shaderName);
        return *this;
    }

    std::string const &RaylibShaderHandle::getName() const {
        return shaderName;
    }

    void RaylibShaderHandle::bindShader() {
        ::BeginShaderMode(material.shader);
    }

    void RaylibShaderHandle::setUniform(std::string const &name, const std::int32_t value) {

        auto defaultLocation = getDefaultMaterialLocation(name);

        if (defaultLocation != -1) {
            material.maps[defaultLocation].value = static_cast<float>(value);
        } else {
            auto location = getLocation(shaderLocations, name, material.shader);

            setShaderUniformValue(material.shader, location, &value, ::SHADER_UNIFORM_INT);
        }
    }

    void RaylibShaderHandle::setUniform(std::string const &name, const std::uint32_t value) {
        auto defaultLocation = getDefaultMaterialLocation(name);

        if (defaultLocation != -1) {
            material.maps[defaultLocation].value = static_cast<float>(value);
        } else {
            setShaderUniformValue(material.shader, getLocation(shaderLocations, name, material.shader), value);
        }
    }

    void RaylibShaderHandle::setUniform(std::string const &name, const float value) {
        auto defaultLocation = getDefaultMaterialLocation(name);

        if (defaultLocation != -1) {
            material.maps[defaultLocation].value = value;
        } else {
            setShaderUniformValue(material.shader, getLocation(shaderLocations, name, material.shader), &value, ::SHADER_UNIFORM_FLOAT);
        }
    }

    void RaylibShaderHandle::setUniform(std::string const &name, Colour const & value) {

        auto defaultLocation = getDefaultMaterialLocation(name);

        if (defaultLocation != -1) {
            material.maps[defaultLocation].color = ::Color{
                 static_cast<unsigned char>(255 * value.r),
                static_cast<unsigned char>(255 * value.g),
                static_cast<unsigned char>(255 * value.b),
                static_cast<unsigned char>(255 * value.a),
            };
        } else {
            auto location = getLocation(shaderLocations, name, material.shader);

            setShaderUniformValue(material.shader, location,
                MathHelper::StructToArrayConverter<Colour, float>::convert(value), ::SHADER_UNIFORM_VEC4);
        }
    }

    void RaylibShaderHandle::setUniform(std::string const &name, Vector2 const & value) {
        setShaderUniformValue(material.shader, getLocation(shaderLocations, name, material.shader),
            MathHelper::StructToArrayConverter<Vector2, float>::convert(value), ::SHADER_UNIFORM_VEC2);
    }

    void RaylibShaderHandle::setUniform(std::string const &name, Vector3 const & value) {
        setShaderUniformValue(material.shader, getLocation(shaderLocations, name, material.shader),
            MathHelper::StructToArrayConverter<Vector3, float>::convert(value), ::SHADER_UNIFORM_VEC3);
    }
    void RaylibShaderHandle::setUniform(std::string const &name, Vector4 const & value) {
        setShaderUniformValue(material.shader, getLocation(shaderLocations, name, material.shader),
            MathHelper::StructToArrayConverter<Vector4, float>::convert(value), ::SHADER_UNIFORM_VEC4);
    }

    void RaylibShaderHandle::setUniform(std::string const &name, Matrix2x2 const & value) {
        setShaderUniformValue(material.shader, getLocation(shaderLocations, name, material.shader), value);
    }

    void RaylibShaderHandle::setUniform(std::string const &name, Matrix3x3 const & value) {
        setShaderUniformValue(material.shader, getLocation(shaderLocations, name, material.shader), value);
    }

    void RaylibShaderHandle::setUniform(std::string const &name, Matrix4x4 const & value) {
        setShaderUniformValue(material.shader, getLocation(shaderLocations, name, material.shader), value);
    }

    void RaylibShaderHandle::setUniform(std::string const &name, ObjectHandle<TextureHandle> value) {
        auto defaultLocation = getDefaultMaterialLocation(name);

        // get the actual texture
        auto const &texture = static_handle_cast<RaylibTextureHandle>(value)->getTexture();

        if (defaultLocation != -1) {
            material.maps[defaultLocation].texture = texture;
        } else {
            // set texture uniform
            setShaderUniformValue(material.shader, getLocation(shaderLocations, name, material.shader), texture);
        }
    }

    ::Material const &RaylibShaderHandle::getMaterial() const {
        return material;
    }

    void RaylibShaderHandle::unbindShader() {
        ::EndShaderMode();
    }

    RaylibShaderHandle::~RaylibShaderHandle() {
        ::UnloadShader(material.shader);
        ::MemFree(material.maps);
    }
}
