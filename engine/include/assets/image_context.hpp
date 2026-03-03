#ifndef IMAGE_CONTEXT_HPP
#define IMAGE_CONTEXT_HPP

namespace cppengine
{
    class ImageContext
    {
    private:

    public:

        virtual ~ImageContext() = 0;
    };

    inline ImageContext::~ImageContext() = default;
}

#endif