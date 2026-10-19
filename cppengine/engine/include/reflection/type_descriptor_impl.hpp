#ifndef TYPE_DESCRIPTOR_IMPL_HPP
#define TYPE_DESCRIPTOR_IMPL_HPP

#include "type_descriptor.hpp"
#include <type_traits>
#include <vector>

#include "illegal_field_operation.hpp"

namespace cppengine {

    template <typename T>
    struct FieldDescriptorCreator;

    template <typename T, typename U, U T::* member, StringLiteral name>
    struct FieldDescriptorCreator<MemberDescriptor<T, U, member, name>> {
        static constexpr bool is_const_member = std::is_const<U>::value;
        using member_descriptor_type = MemberDescriptor<T, U, member, name>;
        using const_getter = void const * (*)(void const *);
        using non_const_getter = void * (*)(void *);
        using setter = void (*)(void *, void const *);

        static constexpr const_getter getConstGetter() {
            return [](void const *owner)->void const * { return &(static_cast<typename member_descriptor_type::owner_type const *>(owner)->*member_descriptor_type::getMember()); };
        }

        static constexpr setter getSetter() {
            if constexpr (is_const_member) {
                return [](void *owner, void const *data) { throw IllegalFieldOperation(TypeDescriptor::getTypeDescriptor<T>(), TypeDescriptor::getTypeDescriptor<U>(), static_cast<char const *>(name)); };
            } else {
                return [](void *owner, void const *data) { *(&(static_cast<typename member_descriptor_type::owner_type *>(owner)->*member_descriptor_type::getMember())) = *static_cast<U const *>(data); };
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

    template <typename T>
    TypeDescriptor const * TypeDescriptorImpl<T>::getSuperType() const {
        return TypeDescriptor::getTypeDescriptor<typename TypeTraits<typename std::remove_cvref<T>::type>::super_type>();
    }

    template<typename T>
    std::span<const FieldDescriptor> TypeDescriptorImpl<T>::getFields() const {
        static const std::vector<FieldDescriptor> fields = createFieldList(this, typename TypeMemberTraits<T>::members());

        return std::span{ fields };
    }

    template <typename T>
    TypeDescriptorImpl<T>::~TypeDescriptorImpl() {}

    template <typename T>
    std::string_view TypeDescriptorImpl<T>::getName() const {
        return TypeTraits<typename std::remove_cvref<T>::type>::getName();
    }

    template<typename T>
    TypeDescriptor const *TypeDescriptor::getTypeDescriptor() {
        static TypeDescriptorImpl<typename std::remove_cvref<T>::type> type;
        return &type;
    }

    template <typename T>
    bool TypeDescriptor::isSuperType(TypeDescriptor const *subType) {
        TypeDescriptor const *superType = TypeDescriptor::getTypeDescriptor<typename std::remove_cvref<T>::type>();
        return isSuperType(superType, subType);
    }
}

#endif