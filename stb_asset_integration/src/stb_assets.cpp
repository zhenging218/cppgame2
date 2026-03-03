#include "engine.hpp"
#include "../include/stb_image_context.hpp"

namespace cppengine
{
    ObjectHandle<ImageContext> Assets::createImageContext()
    {
        return new StbImageContext();
    }
}
