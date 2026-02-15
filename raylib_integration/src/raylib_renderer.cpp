#include "engine.hpp"
#include "raylib_integration.hpp"

namespace cppengine {
    ObjectHandle<RendererContext> Renderer::createContext() {
        return ObjectHandle(new RaylibRendererContext());
    }
}
