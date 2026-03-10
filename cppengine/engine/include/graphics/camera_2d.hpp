#ifndef CAMERA_2D_HPP
#define CAMERA_2D_HPP

#include "camera.hpp"

namespace cppengine {
    class Camera2D : public Camera {
    private:

    public:
        CameraMode getMode() const override;
        ~Camera2D() override = default;
    };
}

DECL_TYPE_DESCRIPTOR(cppengine::Camera2D, cppengine::Camera)

#endif