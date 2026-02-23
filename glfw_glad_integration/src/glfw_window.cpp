#include "engine.hpp"
#include "gg_integration.hpp"

namespace cppengine {
    ObjectHandle<WindowContext> Window::createContext() {
        return GGContextManager::getWindowContext();
    }
}
