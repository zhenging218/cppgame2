#include <filesystem>

#include "engine.hpp"

namespace cppengine {
    namespace ShaderHelper {
        std::pair<std::string, std::string> getShaderSourcePaths(std::string_view name) {
            /*
            std::filesystem::path path = Assets::getDirectory("./assets/shaders", name);
            return {(path / (name + ".vert")).string(), (path / (name + ".frag")).string()};
            */
            return {};
        }
    }
}