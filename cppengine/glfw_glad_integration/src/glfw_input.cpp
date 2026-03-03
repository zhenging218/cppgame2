#include "engine.hpp"
#include "gg_integration.hpp"

namespace cppengine {
    ObjectHandle<InputContext> Input::createContext() {
        return GGContextManager::getInputContext();
    }
}
