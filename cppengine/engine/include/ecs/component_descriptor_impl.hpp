#ifndef COMPONENT_DESCRIPTOR_IMPL_HPP
#define COMPONENT_DESCRIPTOR_IMPL_HPP

namespace cppengine {
    template <typename T>
    ComponentDescriptor const *ComponentDescriptor::getComponentDescriptor() {
        static const ComponentDescriptorImpl<T> descriptor(TypeDescriptor::getTypeDescriptor<T>());
        return &descriptor;
    }

    template <typename T>
    ComponentDescriptorImpl<T>::ComponentDescriptorImpl(TypeDescriptor const *descriptor_) : descriptor(descriptor_) {}

    template <typename T>
    bool ComponentDescriptorImpl<T>::isSuperType(ComponentDescriptor const *subType) const {
        return TypeDescriptor::isSuperType(descriptor, subType->getDescriptor());
    }

    template <typename T>
    TypeDescriptor const *ComponentDescriptorImpl<T>::getDescriptor() const {
        return descriptor;
    }

    template <typename T>
    void ComponentDescriptorImpl<T>::init(ObjectHandle<Component> const &component) const {
        if constexpr (SceneInitialisableType<T>) {
            static_handle_cast<T>(component)->init();
        }
    }

    template <typename T>
    void ComponentDescriptorImpl<T>::update(ObjectHandle<Component> const &component) const {
        if constexpr (SceneUpdatableType<T>) {
            static_handle_cast<T>(component)->update();
        }
    }

    template <typename T>
    void ComponentDescriptorImpl<T>::dispose(ObjectHandle<Component> const &component) const {
        if constexpr (SceneDisposableType<T>) {
            static_handle_cast<T>(component)->dispose();
        }
    }

    template <typename T>
    void ComponentDescriptorImpl<T>::init(std::unordered_map<std::uint64_t, ObjectHandle<Component>> const &components) const {
        if constexpr (SceneInitialisableType<T>) {
            auto copy = components;
            std::ranges::for_each(copy, [this](auto const &component) {
               init(component.second);
            });
        }
    }

    template <typename T>
    void ComponentDescriptorImpl<T>::update(std::unordered_map<std::uint64_t, ObjectHandle<Component>> const &components) const {
        if constexpr (SceneUpdatableType<T>) {
            auto copy = components;
            std::ranges::for_each(copy, [this](auto const &component) {
               update(component.second);
            });
        }
    }

    template <typename T>
    void ComponentDescriptorImpl<T>::dispose(std::unordered_map<std::uint64_t, ObjectHandle<Component>> const &components) const {
        if constexpr (SceneDisposableType<T>) {
            auto copy = components;
            std::ranges::for_each(copy, [this](auto const &component) {
               dispose(component.second);
            });
        }
    }
}

#endif