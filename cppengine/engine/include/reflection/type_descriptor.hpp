#ifndef TYPE_DESCRIPTOR_H
#define TYPE_DESCRIPTOR_H

#include <span>
#include <typeinfo>
#include <string_view>

namespace cppengine {

    struct TypeMemberDescriptor;

    class TypeDescriptor {
    private:
        template <typename T>
        friend struct TypeHierarchy;

        template <typename T, typename U>
        static TypeMemberDescriptor getTypeMemberDescriptor(char const *name, U T::* member);

    public:

        template <typename T>
        static TypeDescriptor const *getTypeDescriptor();

        virtual TypeDescriptor const *getSuperType() const = 0;
        virtual std::string_view getName() const = 0;
        virtual ~TypeDescriptor() = default;

        template <typename T>
        static bool isSuperType(TypeDescriptor const *descriptor);

        static bool isSuperType(TypeDescriptor const *superType, TypeDescriptor const *subType);
    };

    template <typename T, typename U, U T::* member, char const *name>
    struct MemberDescriptor {
        static constexpr char const * getName() { return name; }
        static U &get(T &instance) { return instance.*member; }
        static U const &get(T const &instance) { return instance.*member; }
    };

    template <typename T>
    struct TypeHierarchy {
        using super_type = T;
        static constexpr std::size_t size = sizeof(T);
        static constexpr char const *getName() { return typeid(T).name(); }
    };

    template <typename T>
    class TypeDescriptorImpl final : public TypeDescriptor {
    private:
        friend class TypeDescriptor;
        TypeDescriptorImpl() = default;

    public:

        TypeDescriptorImpl(TypeDescriptorImpl const &) = delete;
        TypeDescriptorImpl(TypeDescriptorImpl &&) = delete;
        TypeDescriptorImpl &operator=(TypeDescriptorImpl const &) = delete;
        TypeDescriptorImpl &operator=(TypeDescriptorImpl &&) = delete;

        TypeDescriptor const * getSuperType() const override;
        std::string_view getName() const override;
    };

}

#define DECL_BASE_TYPE(NS_QUALIFIED_TYPE_NAME, ...) \
namespace cppengine {\
    template<> \
    struct TypeHierarchy<NS_QUALIFIED_TYPE_NAME> { \
        using type = NS_QUALIFIED_TYPE_NAME; \
        using super_type = NS_QUALIFIED_TYPE_NAME; \
        static constexpr char const * getName() { return #NS_QUALIFIED_TYPE_NAME; } \
    }; \
}

#define DECL_POLY_TYPE(NS_QUALIFIED_TYPE_NAME, NS_QUALIFIED_SUPER_TYPE_NAME, ...) \
namespace cppengine {\
    template<> \
    struct TypeHierarchy<NS_QUALIFIED_TYPE_NAME> { \
        using type = NS_QUALIFIED_TYPE_NAME; \
        using super_type = NS_QUALIFIED_SUPER_TYPE_NAME; \
        static constexpr char const * getName() { return #NS_QUALIFIED_TYPE_NAME; } \
    }; \
}

#define GET_DECL_TYPE_MACRO(_1, _2, MACRO, ...) MACRO
#define DECL_TYPE_DESCRIPTOR(...) GET_DECL_TYPE_MACRO(__VA_ARGS__, DECL_POLY_TYPE, DECL_BASE_TYPE)(__VA_ARGS__)

#endif