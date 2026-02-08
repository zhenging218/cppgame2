#ifndef TYPE_DESCRIPTOR_H
#define TYPE_DESCRIPTOR_H

namespace cppengine {
    class TypeDescriptor {
    public:

        template <typename T>
        static TypeDescriptor const *getTypeDescriptor();

        virtual ~TypeDescriptor() = 0;
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
        virtual ~TypeDescriptorImpl() override {}
    };

    template<typename T>
    TypeDescriptor const *TypeDescriptor::getTypeDescriptor() {
        static TypeDescriptorImpl<T> type;
        return &type;
    }
}


#endif