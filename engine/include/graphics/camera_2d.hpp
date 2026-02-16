#ifndef CAMERA_2D_HPP
#define CAMERA_2D_HPP

#include "camera.hpp"

namespace cppengine {
    class Camera2D : public Camera {
    private:

    public:
        CameraMode getMode() const override;
    };
}

#endif