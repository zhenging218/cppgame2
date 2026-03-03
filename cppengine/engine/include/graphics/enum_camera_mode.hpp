#ifndef ENUM_CAMERA_MODE_HPP
#define ENUM_CAMERA_MODE_HPP

namespace cppengine {
    enum class CameraMode {
        MODE_2D = 1,
        MODE_3D_PERSPECTIVE = 2,
        MODE_3D_ORTHOGRAPHIC = 3,
        MODE_UI = 4
    };

    auto inline operator<=>(CameraMode const &lhs, CameraMode const &rhs) { return static_cast<int>(lhs) <=> static_cast<int>(rhs); }
    auto inline operator==(CameraMode const &lhs, CameraMode const &rhs) { return static_cast<int>(lhs) == static_cast<int>(rhs); }
}

#endif