#ifndef TYPE_DESCRIPTOR_H
#define TYPE_DESCRIPTOR_H
#include <vector>

namespace cppengine {
    class TypeDescriptor {
    public:

        template <typename T>
        static TypeDescriptor const *getTypeDescriptor();

        virtual TypeDescriptor const *getSuperType() const = 0;
        virtual ~TypeDescriptor() = default;

        template <typename T>
        static bool isSuperType(TypeDescriptor const *descriptor);

        static bool isSuperType(TypeDescriptor const *superType, TypeDescriptor const *subType);
    };

    template <typename T>
        struct TypeHierarchy {
        using super_type = T;
    };

    template <typename T>
    class TypeDescriptorImpl final : public TypeDescriptor {
    private:


        friend class TypeDescriptor;
        TypeDescriptorImpl() = default;
        TypeDescriptorImpl(TypeDescriptorImpl const &) = delete;
        TypeDescriptorImpl(TypeDescriptorImpl &&) = delete;
        TypeDescriptorImpl &operator=(TypeDescriptorImpl const &) = delete;
        TypeDescriptorImpl &operator=(TypeDescriptorImpl &&) = delete;
    public:

        TypeDescriptor const * getSuperType() const override {
            return TypeDescriptor::getTypeDescriptor<typename TypeHierarchy<T>::super_type>();
        }
    };

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

#define DECL_POLY_TYPE(NS_QUALIFIED_TYPE_NAME, NS_QUALIFIED_SUPER_TYPE_NAME) \
    namespace cppengine {\
        template<> struct TypeHierarchy<NS_QUALIFIED_TYPE_NAME> { using super_type = NS_QUALIFIED_SUPER_TYPE_NAME; };\
    }

#endif