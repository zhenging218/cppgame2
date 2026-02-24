#include <filesystem>

#include "engine.hpp"

namespace cppengine {
    namespace ShaderHelper {
        std::pair<std::string, std::string> getShaderSourcePaths(std::string const &name) {
            std::filesystem::path path = Assets::getDirectory("./assets/shaders", name);
            return {(path / (name + ".vert")).string(), (path / (name + ".frag")).string()};
        }
    }
}