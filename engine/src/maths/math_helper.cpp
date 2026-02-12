#include "maths/math_helper.hpp"

namespace cppengine {
    namespace MathHelper {
        float determinant2D(const float &v,
     const float &a, const float &b,
     const float &c, const float &d) {
            return v * (a * d - c * b);
        }

        float determinant3D(const float &v,
                const float& a, const float& b, const float &c,
                const float& d, const float& e, const float &f,
                const float &g, const float &h, const float &i) {
            return v * determinant2D(a, e, f, g, i) - determinant2D(b, d, f, g, i) + determinant2D(c, d, e, g, h);
        }
    }

}