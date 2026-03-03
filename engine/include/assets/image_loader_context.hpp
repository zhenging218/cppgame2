#ifndef IMAGE_LOADER_CONTEXT_HPP
#define IMAGE_LOADER_CONTEXT_HPP

namespace cppengine
{
    class ImageLoaderContext
    {
    private:

    public:

        virtual ~ImageLoaderContext() = 0;
    };

    inline ImageLoaderContext::~ImageLoaderContext() = default;
}

#endif