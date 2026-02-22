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
        ShaderID shaderId;
        std::unordered_map<std::string, Uniform> uniforms;
        std::unordered_map<std::string, Texture> textures;

    public:
        Material();

        ShaderID getShaderId() const;

        // todo: shader asset system, so setShader can set by name only
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
    };
}

#endif
