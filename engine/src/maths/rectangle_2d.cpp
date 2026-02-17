#include "engine.hpp"

namespace cppengine {

    namespace {
        constexpr float epsilon = std::numeric_limits<float>::epsilon();
    }

    bool operator==(Rectangle2D const &lhs, Rectangle2D const &rhs) {
        return &lhs == &rhs ||
            (
                std::abs(rhs.x - lhs.x) < epsilon
                && std::abs(rhs.y - lhs.y) < epsilon
                && std::abs(rhs.width - lhs.width) < epsilon
                && std::abs(rhs.height - lhs.height) < epsilon
            );
    }
}