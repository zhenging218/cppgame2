#ifndef TYPE_DESCRIPTOR_IMPL_HPP
#define TYPE_DESCRIPTOR_IMPL_HPP

#include "type_descriptor.hpp"

namespace cppengine {
    template <typename T>
    TypeDescriptor const * TypeDescriptorImpl<T>::getSuperType() const {
        return TypeDescriptor::getTypeDescriptor<typename TypeHierarchy<T>::super_type>();
    }

    template <typename T>
    std::string_view TypeDescriptorImpl<T>::getName() const {
        return TypeHierarchy<T>::getName();
    }

    template<typename T>
    TypeDescriptor const *TypeDescriptor::getTypeDescriptor() {
        static TypeDescriptorImpl<T> type;
        return &type;
    }

    template <typename T>
    bool TypeDescriptor::isSuperType(TypeDescriptor const *subType) {
        TypeDescriptor const *superType = TypeDescriptor::getTypeDescriptor<T>();
        return isSuperType(superType, subType);
    }
}

#endif