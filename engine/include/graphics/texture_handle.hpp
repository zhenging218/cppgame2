#ifndef TEXTURE_HANDLE_HPP
#define TEXTURE_HANDLE_HPP
#include <cstddef>

namespace cppengine {
    class TextureHandle {
    private:

    public:
        virtual ~TextureHandle() = 0;
    };

    inline TextureHandle::~TextureHandle() = default;
}

#endif