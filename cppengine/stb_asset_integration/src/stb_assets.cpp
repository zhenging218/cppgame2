#include "engine.hpp"
#include "stb_assets_pch.hpp"

namespace cppengine
{
    ObjectHandle<ImageContext> Assets::createImageContext()
    {
        return new StbImageContext();
    }
}
