#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "ecs/component.hpp"
#include "enum_camera_mode.hpp"
#include "maths/rectangle_2d.hpp"

namespace cppengine {
    class Camera : public Component {
    private:
        Rectangle2D viewport;

    protected:
        Camera() = default;
        Camera(float x, float y, float width, float height);

    public:
        virtual CameraMode getMode() const = 0;
        ~Camera() override = 0;

        void setXOffset(float xOffset);
        float getXOffset() const;

        void setYOffset(float yOffset);
        float getYOffset() const;

        void setViewportWidth(float viewportWidth);
        float getViewportWidth() const;

        void setViewportHeight(float viewportHeight);
        float getViewportHeight() const;

        Rectangle2D const &getViewport() const;
        void setViewport(Rectangle2D const &v);
    };

    inline Camera::~Camera() = default;
}

#endif
