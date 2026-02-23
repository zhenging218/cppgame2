#include "engine.hpp"
#include "gg_integration.hpp"

namespace cppengine {
    GGContextManager::GGContextManager() : windowContext(new GLFWWindowContext()) {

    }

    GGContextManager &GGContextManager::getInstance() {
        static GGContextManager instance;
        return instance;
    }

    ObjectHandle<GLFWWindowContext> GGContextManager::getWindowContext() {
        auto &instance = getInstance();
    }
}
