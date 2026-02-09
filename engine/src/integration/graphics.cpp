#include "engine.hpp"

namespace cppengine {
    Graphics::Graphics() {

    }

    void Graphics::initialise() {

    }

    void Graphics::shutdown() {

    }

    void Graphics::beginDraw() {

    }

    void Graphics::draw() {

    }

    void Graphics::endDraw() {

    }

    Graphics &Graphics::getInstance() {
        static Graphics graphics;
        return graphics;
    }
}
