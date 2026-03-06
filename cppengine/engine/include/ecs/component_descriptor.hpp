#ifndef COMPONENT_DESCRIPTOR_HPP
#define COMPONENT_DESCRIPTOR_HPP
#include <algorithm>
#include <iostream>
#include <unordered_map>

namespace cppengine {
    class Component;

    template <typename T>
    concept SceneUpdatableType = requires { std::declval<T&>().update(); };

    template <typename T>
    concept SceneInitialisableType = requires { std::declval<T&>().init(); };

    template <typename T>
    concept SceneDisposableType = requires { std::declval<T&>().dispose(); };

    struct ComponentDescriptor {
        virtual bool isSuperType(ComponentDescriptor const *subType) const = 0;
        virtual TypeDescriptor const *getDescriptor() const = 0;
        virtual void init(ObjectHandle<Component> const &component) const = 0;
        virtual void update(ObjectHandle<Component> const &component) const = 0;
        virtual void dispose(ObjectHandle<Component> const &component) const = 0;
        virtual void init(std::unordered_map<std::uint64_t, ObjectHandle<Component>> const &components) const = 0;
        virtual void update(std::unordered_map<std::uint64_t, ObjectHandle<Component>> const &components) const = 0;
        virtual void dispose(std::unordered_map<std::uint64_t, ObjectHandle<Component>> const &components) const = 0;
        virtual ~ComponentDescriptor() = default;

        template <typename T>
        static ComponentDescriptor const *getComponentDescriptor();
    };

    template <typename T>
    struct ComponentDescriptorImpl : ComponentDescriptor {
        TypeDescriptor const *descriptor;

        ComponentDescriptorImpl(TypeDescriptor const *descriptor_);
        ComponentDescriptorImpl(ComponentDescriptorImpl const &) = delete;
        ComponentDescriptorImpl &operator=(ComponentDescriptorImpl const &) = delete;

        bool isSuperType(ComponentDescriptor const *subType) const override;
        TypeDescriptor const *getDescriptor() const override;
        void init(ObjectHandle<Component> const &component) const override;
        void update(ObjectHandle<Component> const &component) const override;
        void dispose(ObjectHandle<Component> const &component) const override;
        void init(std::unordered_map<std::uint64_t, ObjectHandle<Component>> const &components) const override;
        void update(std::unordered_map<std::uint64_t, ObjectHandle<Component>> const &components) const override;
        void dispose(std::unordered_map<std::uint64_t, ObjectHandle<Component>> const &components) const override;
    };
}

#endif