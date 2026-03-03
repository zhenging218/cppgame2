#include "engine.hpp"
#include "gg_integration.hpp"

namespace cppengine {

    GGContextManager &GGContextManager::getInstance() {
        static GGContextManager instance;
        return instance;
    }

    ObjectHandle<GLFWWindowContext> GGContextManager::getWindowContext() {
        auto &instance = getInstance();
        if (instance.windowContext == nullptr) {
            instance.windowContext = ObjectHandle(new GLFWWindowContext());
        }
        return instance.windowContext;
    }


    ObjectHandle<GLFWInputContext> GGContextManager::getInputContext() {
        auto &instance = getInstance();
        if (instance.inputContext == nullptr) {
            instance.inputContext = ObjectHandle(new GLFWInputContext());
        }
        return instance.inputContext;
    }
}
