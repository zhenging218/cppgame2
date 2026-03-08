#ifndef POD_TYPE_DESCRIPTOR_HPP
#define POD_TYPE_DESCRIPTOR_HPP

#include "type_descriptor.hpp"
#include <string>

#define DECL_POD_TYPE(TYPE) \
template<> struct TypeHierarchy<TYPE> { \
    using super_type = TYPE; \
    static constexpr std::size_t size = sizeof(TYPE); \
    static constexpr char const* getName() { return #TYPE; } \
} \

namespace cppengine {
    DECL_POD_TYPE(char);
    DECL_POD_TYPE(short);
    DECL_POD_TYPE(int);
    DECL_POD_TYPE(long);
    DECL_POD_TYPE(long long);

    DECL_POD_TYPE(unsigned char);
    DECL_POD_TYPE(unsigned short);
    DECL_POD_TYPE(unsigned int);
    DECL_POD_TYPE(unsigned long);
    DECL_POD_TYPE(unsigned long long);

    DECL_POD_TYPE(float);
    DECL_POD_TYPE(double);
    DECL_POD_TYPE(std::string);
}

#undef DECL_POD_TYPE

#endif
