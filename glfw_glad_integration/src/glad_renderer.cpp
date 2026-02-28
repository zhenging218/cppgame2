#include "engine.hpp"
#include "gg_integration.hpp"

namespace cppengine {
    ObjectHandle<RendererContext> Renderer::createContext() {
        return new GladRendererContext();
    }
}
