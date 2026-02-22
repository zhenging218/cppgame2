#include <filesystem>

#include "engine.hpp"

namespace cppengine {
    std::pair<std::string, std::string> ShaderContext::getShaderSourcePaths(std::string const &name) const {
        std::filesystem::path path = Assets::getDirectory("./assets/shaders", name);
        return {(path / (name + ".vert")).string(), (path / (name + ".frag")).string()};
    }
}
