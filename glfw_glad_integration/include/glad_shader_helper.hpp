#ifndef GLAD_SHADER_HELPER_HPP
#define GLAD_SHADER_HELPER_HPP
#include <format>
#include <stdexcept>

#include "glad/gl.h"

namespace cppengine {
    namespace GladShaderHelper {
        GLuint compileShader(char const *vertPath, char const *fragPath,
            char const *vertSource, char const *fragSource);
    }
}

#endif