#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "ecs/component.hpp"
#include "enum_camera_mode.hpp"

namespace cppengine {
    class Camera : public Component {
    public:
        virtual CameraMode getMode() const = 0;
        virtual ~Camera() override = 0;
    };

    inline Camera::~Camera() = default;
}

#endif
