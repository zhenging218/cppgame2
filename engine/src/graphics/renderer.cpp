#include "engine.hpp"

namespace cppengine {
    Renderer::Renderer() {

    }

    void Renderer::initialise() {

    }

    void Renderer::shutdown() {

    }

    void Renderer::beginDraw() {

    }

    void Renderer::draw() {

    }

    void Renderer::endDraw() {

    }

    Renderer &Renderer::getInstance() {
        static Renderer Renderer;
        return Renderer;
    }
}
