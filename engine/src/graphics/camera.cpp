#include "engine.hpp"

namespace cppengine {
    Camera::Camera(float x, float y, float width, float height)
     : viewport(x, y, width, height) {

    }

    void Camera::setXOffset(float xOffset) {
        viewport.x = xOffset;
    }

    void Camera::setYOffset(float yOffset) {
        viewport.y = yOffset;
    }

    void Camera::setViewportWidth(float viewportWidth) {
        viewport.width = viewportWidth;
    }

    void Camera::setViewportHeight(float viewportHeight) {
        viewport.height = viewportHeight;
    }

    void Camera::setViewport(Rectangle2D const &v) {
        viewport = v;
    }

    float Camera::getXOffset() const {
        return viewport.x;
    }

    float Camera::getYOffset() const {
        return viewport.y;
    }

    float Camera::getViewportWidth() const {
        return viewport.width;
    }

    float Camera::getViewportHeight() const {
        return viewport.height;
    }

    Rectangle2D const &Camera::getViewport() const {
        return viewport;
    }
}
