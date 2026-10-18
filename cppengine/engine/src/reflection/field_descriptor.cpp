//
// Created by Admin on 18/10/2026.
//

#include "engine.hpp"

namespace cppengine {
    FieldDescriptor::FieldDescriptor(char const *name_, TypeDescriptor const *descriptor_, getter_type getter_, const_getter_type const_getter_)
            : name(name_), descriptor(descriptor_), getter(getter_), const_getter(const_getter_) {}

    char const *FieldDescriptor::getName() const { return name; }

    TypeDescriptor const *FieldDescriptor::getTypeDescriptor() const { return descriptor; }

    void *FieldDescriptor::get(void *src) const {
        return getter(src);
    }

    void const *FieldDescriptor::get(void const *src) const {
        return const_getter(src);
    }
}