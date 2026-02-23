#include "engine.hpp"
#include "gg_integration.hpp"
#include "../include/glfw_window_context.hpp"

namespace cppengine {
    ObjectHandle<WindowContext> Window::createContext() {
        return ObjectHandle(new GLFWWindowContext());
    }
}
