#ifndef SHADER_HELPER_HPP
#define SHADER_HELPER_HPP
#include <string>
#include <utility>

namespace cppengine {
    namespace ShaderHelper {
        std::pair<std::string, std::string> getShaderSourcePaths(std::string const &name);
    }
}

#endif