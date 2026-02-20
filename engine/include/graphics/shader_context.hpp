#ifndef SHADER_CONTEXT_HPP
#define SHADER_CONTEXT_HPP

namespace cppengine {
    class ShaderContext {
    private:

    public:
        virtual ~ShaderContext() = 0;
    };

    inline ShaderContext::~ShaderContext() = default;
}

#endif