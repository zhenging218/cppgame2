//
// Created by Admin on 18/10/2026.
//

#ifndef FIELD_DESCRIPTOR_HPP
#define FIELD_DESCRIPTOR_HPP

namespace cppengine {
    class TypeDescriptor;

    class FieldDescriptor {
    private:
        using getter_type = void const *(*)(void const *);
        using setter_type = void (*)(void *, void const *);

        char const *name;
        TypeDescriptor const *owner;
        TypeDescriptor const *descriptor;
        getter_type getter;
        setter_type setter;

    public:
        FieldDescriptor(char const *name_,TypeDescriptor const * owner_, TypeDescriptor const *descriptor_, getter_type getter_, setter_type setter_);
        char const *getName() const;
        TypeDescriptor const *getOwner() const;
        TypeDescriptor const *getTypeDescriptor() const;

        void const * get(void const *src) const;

        void set(void *dest, void const *src) const;
    };
}

#endif //FIELD_DESCRIPTOR_HPP