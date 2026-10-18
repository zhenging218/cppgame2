#ifndef TYPE_DESCRIPTOR_IMPL_HPP
#define TYPE_DESCRIPTOR_IMPL_HPP

#include "type_descriptor.hpp"
#include <type_traits>
#include <vector>

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

        // todo: refactor to use concepts and static_assert on illegal calls to getNonConstGetter and getSetter when is_const_member is true

        static constexpr non_const_getter getNonConstGetter() {

            if constexpr (is_const_member) {
                return [](void *owner)->void * { return nullptr; };
            } else {
                return [](void *owner)->void * { return &(static_cast<typename member_descriptor_type::owner_type *>(owner)->*member_descriptor_type::getMember()); };
            }

        }

        static constexpr const_getter getConstGetter() {
            return [](void const *owner)->void const * { return &(static_cast<typename member_descriptor_type::owner_type const *>(owner)->*member_descriptor_type::getMember()); };
        }

        static constexpr setter getSetter() {
            if constexpr (is_const_member) {
                return [](void *owner, void const *data) {};
            } else {
                return [](void *owner, void const *data) { *(&(static_cast<typename member_descriptor_type::owner_type *>(owner)->*member_descriptor_type::getMember())) = *static_cast<U const *>(data); };
            }
        }

        static FieldDescriptor createFieldDescriptor() {

            return FieldDescriptor(
                member_descriptor_type::getName(),
                TypeDescriptor::getTypeDescriptor<typename std::remove_cvref<typename member_descriptor_type::field_type>::type>()
                    , getNonConstGetter()
                    , getConstGetter()
                    , getSetter());
        }
    };

    template <typename T>
    std::vector<FieldDescriptor> createFieldList(T &&);

    template <typename ... MemberDescriptors>
    std::vector<FieldDescriptor> createFieldList(ArgumentList<MemberDescriptors...> &&) {
        return { FieldDescriptorCreator<MemberDescriptors>::createFieldDescriptor()... };
    }

    template <typename T>
    TypeDescriptor const * TypeDescriptorImpl<T>::getSuperType() const {
        return TypeDescriptor::getTypeDescriptor<typename TypeTraits<typename std::remove_cvref<T>::type>::super_type>();
    }

    template<typename T>
    std::span<const FieldDescriptor> TypeDescriptorImpl<T>::getFields() const {
        static const std::vector<FieldDescriptor> fields = createFieldList(typename TypeMemberTraits<T>::members());

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