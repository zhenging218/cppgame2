//
// Created by Admin on 18/10/2026.
//

#include "engine.hpp"

namespace cppengine {
    FieldDescriptor::FieldDescriptor(char const *name_, TypeDescriptor const * owner_, TypeDescriptor const *descriptor_, getter_type getter_, setter_type setter_)
            : name(name_), owner(owner_), descriptor(descriptor_), getter(getter_), setter(setter_) {}

    char const *FieldDescriptor::getName() const { return name; }

    TypeDescriptor const *FieldDescriptor::getOwner() const { return owner; }
    TypeDescriptor const *FieldDescriptor::getTypeDescriptor() const { return descriptor; }

    void const *FieldDescriptor::get(void const *src) const {
        return getter(src);
    }

    void FieldDescriptor::set(void *dest, void const *src) const {
        setter(dest, src);
    }
}
