#ifndef TYPE_DESCRIPTOR_IMPL_HPP
#define TYPE_DESCRIPTOR_IMPL_HPP

#include "type_descriptor.hpp"
#include <type_traits>
#include <vector>

#include "illegal_field_operation.hpp"

namespace cppengine {

    template <typename T>
    struct FieldDescriptorCreator;

    template <typename T, StringLiteral name, typename U, U T::* member, auto getter, auto setter>
    struct FieldDescriptorCreator<MemberDescriptor<T, name, U, member, getter, setter>> {
        static constexpr bool is_const_member = std::is_const<U>::value;
        using member_descriptor_type = MemberDescriptor<T, name, U, member, getter, setter>;
        using const_getter_type = void const * (*)(void const *);
        using non_const_getter_type = void * (*)(void *);
        using setter_type = void (*)(void *, void const *);

        static constexpr const_getter_type getConstGetter() {
            return [](void const *owner)->void const * {
                return &member_descriptor_type::get(*static_cast<member_descriptor_type::owner_type const *>(owner));
            };
        }

        static constexpr setter_type getSetter() {
            if constexpr (is_const_member) {
                return [](void *, void const *) { throw IllegalFieldOperation(TypeDescriptor::getTypeDescriptor<T>(), TypeDescriptor::getTypeDescriptor<U>(), name.data()); };
            } else {
                return [](void *owner, void const *data) { member_descriptor_type::set(*static_cast<member_descriptor_type::owner_type *>(owner), *static_cast<U const *>(data)); };
            }
        }

        static FieldDescriptor createFieldDescriptor(TypeDescriptor const *owner) {

            return FieldDescriptor(
                member_descriptor_type::getName(),
                owner,
                TypeDescriptor::getTypeDescriptor<typename std::remove_cvref<typename member_descriptor_type::field_type>::type>()
                    , getConstGetter()
                    , getSetter());
        }
    };

    template <typename T>
    std::vector<FieldDescriptor> createFieldList(TypeDescriptor const * owner, T &&);

    template <typename ... MemberDescriptors>
    std::vector<FieldDescriptor> createFieldList(TypeDescriptor const * owner, ArgumentList<MemberDescriptors...> &&) {
        return { FieldDescriptorCreator<MemberDescriptors>::createFieldDescriptor(owner)... };
    }

    template <typename T> requires std::same_as<T, std::remove_cvref_t<T>>
    TypeDescriptor const * TypeDescriptorImpl<T>::getSuperType() const {
        return TypeDescriptor::getTypeDescriptor<typename TypeTraits<typename std::remove_cvref<T>::type>::super_type>();
    }

    template<typename T> requires std::same_as<T, std::remove_cvref_t<T>>
    std::span<const FieldDescriptor> TypeDescriptorImpl<T>::getFields() const {
        static const std::vector<FieldDescriptor> fields = createFieldList(this, typename TypeMemberTraits<T>::members());

        return std::span{ fields };
    }

    template <typename T> requires std::same_as<T, std::remove_cvref_t<T>>
    TypeDescriptorImpl<T>::~TypeDescriptorImpl() = default;

    template <typename T> requires std::same_as<T, std::remove_cvref_t<T>>
    std::string_view TypeDescriptorImpl<T>::getName() const {
        return TypeTraits<typename std::remove_cvref<T>::type>::getName();
    }

    template<typename T>
    TypeDescriptor const *TypeDescriptor::getTypeDescriptor() {
        return TypeDescriptorImpl<std::remove_cvref_t<T>>::getTypeDescriptor();
    }

    template <typename T>
    bool TypeDescriptor::isSuperType(TypeDescriptor const *subType) {
        TypeDescriptor const *superType = TypeDescriptor::getTypeDescriptor<T>();
        return isSuperType(superType, subType);
    }

    template<typename T> requires std::same_as<T, std::remove_cvref_t<T>>
    TypeDescriptor const *TypeDescriptorImpl<T>::getTypeDescriptor() {
        static TypeDescriptorImpl descriptor;
        return &descriptor;
    }

    template <typename T>
    TypeDescriptor const *TypeDescriptor::getRootDescriptor() {
        auto descriptor = TypeDescriptor::getTypeDescriptor<T>();

        while (descriptor->getSuperType() != descriptor) {
            descriptor = descriptor->getSuperType();
        }

        return descriptor;
    }
}

#endif