//
// Created by Admin on 18/10/2026.
//

#ifndef FIELD_DESCRIPTOR_HPP
#define FIELD_DESCRIPTOR_HPP

namespace cppengine {
    class TypeDescriptor;

    class FieldDescriptor {
    private:
        using getter_type = void *(*)(void*);
        using const_getter_type = void const *(*)(void const *);

        char const *name;
        TypeDescriptor const *descriptor;
        getter_type getter;
        const_getter_type const_getter;

    public:
        FieldDescriptor(char const *name_, TypeDescriptor const *descriptor_, getter_type getter_, const_getter_type const_getter_);
        char const *getName() const;
        TypeDescriptor const *getTypeDescriptor() const;

        template <typename T>
        T const * get(void const *src) const;

        template <typename T>
        T * get(void *src) const;
    };
}

#endif //FIELD_DESCRIPTOR_HPP