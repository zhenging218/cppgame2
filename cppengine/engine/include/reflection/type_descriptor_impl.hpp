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
}

#endif