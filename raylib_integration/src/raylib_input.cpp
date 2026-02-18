#include "engine.hpp"
#include "raylib_integration.hpp"

namespace cppengine {
    ObjectHandle<InputContext> Input::createContext() {
        return ObjectHandle(new RaylibInputContext());
    }
}
