#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <map>
#include <optional>

#include "ecs/component.hpp"

namespace cppengine {
    template <typename T, typename U>
    struct IsUniformType;

    template <typename T, typename ... Args>
    struct IsUniformType<T, std::variant<Args...>>
        : std::disjunction<std::is_same<T, Args>...>{

    };

    template <typename T>
    concept UniformType = IsUniformType<T, Uniform>::value;

    class Material : public Component {
    private:

        std::string shaderName = DEFAULT_SHADER_NAME;
        std::unordered_map<std::string, Uniform> uniforms;
        std::unordered_map<std::string, Texture> textures;

    public:

        std::string_view getShaderName() const;

        void setShader(std::string const &name);

        template<typename T> requires UniformType<T>
        void setUniform(std::string const &name, T &&uniform) {
            uniforms[name] = uniform;
        }

        template <typename T> requires UniformType<T>
        std::optional<T> getUniform(std::string const &name) const {
            auto result = uniforms.find(name);
            if (result == uniforms.end()) {
                return std::nullopt;
            }

            T const* value = std::get_if<T>(&result->second);
            if (!value) {
                return std::nullopt;
            }

            return *value;
        }

        std::unordered_map<std::string, Uniform> const &getUniforms() const;

        ENABLE_REFLECTION();
    };
}

DECL_TYPE_DESCRIPTOR(cppengine::Material, cppengine::Component)

DECL_TYPE_MEMBERS(cppengine::Material)
    DECL_TYPE_MEMBER_FIELD(shaderName),
    DECL_TYPE_MEMBER_FIELD(uniforms),
    DECL_TYPE_MEMBER_FIELD(textures)
END_DECL_TYPE_MEMBERS();

#endif
