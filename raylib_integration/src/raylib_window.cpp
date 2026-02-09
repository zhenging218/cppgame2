#include "engine.hpp"
#include "raylib_integration.hpp"

namespace cppengine {
    ObjectHandle<WindowContext> Window::createContext() {
        return ObjectHandle(new RaylibWindowContext());
    }
}
