#ifndef POD_DESCRIPTOR_HPP
#define POD_DESCRIPTOR_HPP

#define DECL_POD_TYPE(TYPE_NAME) \
    template <> \
    struct TypeTraits<TYPE_NAME> { \
        using super_type = TYPE_NAME; \
        static constexpr std::size_t size = sizeof(TYPE_NAME); \
        static constexpr char const *getName() { return #TYPE_NAME; } \
        static constexpr bool defined_trait_v = false; \
        static constexpr bool pod_type_v = true; \
    }

namespace cppengine {
    DECL_POD_TYPE(char);
    DECL_POD_TYPE(unsigned char);
    DECL_POD_TYPE(short);
    DECL_POD_TYPE(unsigned short);
    DECL_POD_TYPE(int);
    DECL_POD_TYPE(unsigned int);
    DECL_POD_TYPE(long);
    DECL_POD_TYPE(unsigned long);
    DECL_POD_TYPE(long long);
    DECL_POD_TYPE(unsigned long long);
    DECL_POD_TYPE(float);
    DECL_POD_TYPE(double);
    DECL_POD_TYPE(bool);
}

#undef DECL_POD_TYPE

#endif