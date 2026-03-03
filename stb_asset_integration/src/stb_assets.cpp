#include "engine.hpp"
#include "../include/stb_image_loader_context.hpp"

namespace cppengine
{
    ObjectHandle<ImageLoaderContext> Assets::createImageLoaderContext()
    {
        return new StbImageLoaderContext();
    }
}
