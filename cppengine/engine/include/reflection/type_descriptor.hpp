#ifndef TYPE_DESCRIPTOR_H
#define TYPE_DESCRIPTOR_H

#include <functional>
#include <span>
#include <string_view>
#include "string_literal.hpp"
#include "reflection_traits.hpp"
#include "member_descriptor.hpp"

namespace cppengine {

    class FieldDescriptor;

    class TypeDescriptor {
    private:
        template <typename T>
        friend struct TypeTraits;

        template <typename T>
        friend struct TypeMemberTraits;

    public:

        template <typename T>
        static TypeDescriptor const *getTypeDescriptor();

        [[nodiscard]] virtual TypeDescriptor const *getSuperType() const = 0;
        [[nodiscard]] virtual std::string_view getName() const = 0;
        [[nodiscard]] virtual std::span<const FieldDescriptor> getFields() const = 0;
        virtual ~TypeDescriptor();

        template <typename T>
        static TypeDescriptor const *getRootDescriptor();

        template <typename T>
        static bool isSuperType(TypeDescriptor const *descriptor);

        static bool isSuperType(TypeDescriptor const *superType, TypeDescriptor const *subType);
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

        [[nodiscard]] TypeDescriptor const * getSuperType() const override;
        [[nodiscard]] std::string_view getName() const override;
        [[nodiscard]] std::span<const FieldDescriptor> getFields() const override;

        ~TypeDescriptorImpl() override;
    };

}

#define ENABLE_REFLECTION() \
    template <typename T> \
    friend struct cppengine::TypeMemberTraits \

#define DECL_BASE_TYPE(NS_QUALIFIED_TYPE_NAME, ...) \
namespace cppengine {\
    template<> \
    struct TypeTraits<NS_QUALIFIED_TYPE_NAME> { \
        using type = NS_QUALIFIED_TYPE_NAME; \
        using super_type = NS_QUALIFIED_TYPE_NAME; \
        static constexpr bool defined_trait_v = true; \
        static constexpr bool pod_type_v = false; \
        static constexpr bool container_type_v = false; \
        static constexpr StringLiteral name{ #NS_QUALIFIED_TYPE_NAME };\
        static constexpr char const * getName() { return name.data(); } \
    }; \
}

#define DECL_POLY_TYPE(NS_QUALIFIED_TYPE_NAME, NS_QUALIFIED_SUPER_TYPE_NAME, ...) \
namespace cppengine {\
    template<> \
    struct TypeTraits<NS_QUALIFIED_TYPE_NAME> { \
        using type = NS_QUALIFIED_TYPE_NAME; \
        using super_type = NS_QUALIFIED_SUPER_TYPE_NAME; \
        static constexpr bool defined_trait_v = true; \
        static constexpr bool pod_type_v = false; \
        static constexpr bool container_type_v = false; \
        static constexpr char const * getName() { return #NS_QUALIFIED_TYPE_NAME; } \
    }; \
}

#define GET_DECL_TYPE_MACRO(_1, _2, MACRO, ...) MACRO
#define DECL_TYPE_DESCRIPTOR(...) GET_DECL_TYPE_MACRO(__VA_ARGS__, DECL_POLY_TYPE, DECL_BASE_TYPE)(__VA_ARGS__)

#define DECL_TYPE_MEMBERS(NS_QUALIFIED_TYPE_NAME) \
namespace cppengine { \
    template <> \
    struct TypeMemberTraits<NS_QUALIFIED_TYPE_NAME> { \
        using type = NS_QUALIFIED_TYPE_NAME; \
        static constexpr bool members_defined_v = true; \
        using members = ArgumentList<

#define DECL_TYPE_MEMBER_FIELD(MEMBER) \
    MemberDescriptor<type, #MEMBER, decltype(type::MEMBER), &type::MEMBER>

#define DECL_TYPE_MEMBER_ACCESSORS(MEMBER, GETTER, SETTER) \
    MemberDescriptor<type, #MEMBER, std::remove_cvref_t<std::invoke_result_t<decltype(&type::GETTER), type const &>>, nullptr, &type::GETTER, &type::SETTER>

#define END_DECL_TYPE_MEMBERS() \
    >; }; }

#endif