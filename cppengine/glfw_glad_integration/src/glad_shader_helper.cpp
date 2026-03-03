#include "engine.hpp"
#include "gg_integration.hpp"

namespace cppengine {
    namespace GladShaderHelper {
        GLuint compileShader(char const *vertPath, char const *fragPath,
            char const *vertSource, char const *fragSource) {
            auto vert = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vert, 1, &vertSource, nullptr);
            glCompileShader(vert);

            auto frag = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(frag, 1, &fragSource, nullptr);
            glCompileShader(frag);

            auto program = glCreateProgram();
            glAttachShader(program, vert);
            glAttachShader(program, frag);
            glLinkProgram(program);

            glDeleteShader(vert);
            glDeleteShader(frag);

            GLint success3;
            glGetProgramiv(program, GL_LINK_STATUS, &success3);

            if (!success3) {
                glDeleteProgram(program);
                throw std::runtime_error(std::format(
                    "Could not link shader programs {} and {}",
                    vertPath, fragPath));
            }

            return program;
        }
    }
}