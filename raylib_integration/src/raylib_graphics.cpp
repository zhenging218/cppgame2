#include "engine.hpp"
#include "raylib_integration.hpp"



namespace cppengine {
    ObjectHandle<GraphicsContext> Graphics::createContext() {
        return ObjectHandle(new RaylibGraphicsContext());
    }
}
