#include "engine.hpp"

namespace cppengine {
    Box2D::vertex_type& Box2D::operator[](int i) {
        return vertices[i];
    }

    Box2D::vertex_type const& Box2D::operator[](int i) const {
        return vertices[i];
    }

    bool operator==(Box2D const& lhs, Box2D const& rhs) {
        return &lhs == &rhs || (lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2] && lhs[3] == rhs[3]);
    }

    std::ostream& operator<<(std::ostream& os, Box2D const& t) {
        os << t.vertices[0] << ", " << t.vertices[1] << ", " << t.vertices[2] << ", " << t.vertices[3];
        return os;
    }
}