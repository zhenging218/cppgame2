#include "maths/triangle.hpp"

Triangle::vertex_type& Triangle::operator[](int i) {
    return vertices[i];
}

Triangle::vertex_type const& Triangle::operator[](int i) const {
    return vertices[i];
}

bool operator==(Triangle const& lhs, Triangle const& rhs) {
    return &lhs == &rhs || (lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2]);
}

std::ostream& operator<<(std::ostream& os, Triangle const& t) {
    os << t.vertices[0] << ", " << t.vertices[1] << ", " << t.vertices[2];
    return os;
}