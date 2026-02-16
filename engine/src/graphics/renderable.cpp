#include "engine.hpp"

namespace cppengine {
    void Renderable::init() {
        transform = getGameObject().getTransform();
    }
}
