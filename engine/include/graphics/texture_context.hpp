#ifndef TEXTURE_CONTEXT_HPP
#define TEXTURE_CONTEXT_HPP

namespace cppengine {
    class TextureContext {
    private:

    public:
        virtual ~TextureContext() = 0;
    };

    inline TextureContext::~TextureContext() = default;
}

#endif