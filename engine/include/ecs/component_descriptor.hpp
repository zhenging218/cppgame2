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
        };

        template <typename T>
        struct ComponentDescriptorImpl : ComponentDescriptor {
            TypeDescriptor const *descriptor;

            ComponentDescriptorImpl(TypeDescriptor const *descriptor_) : descriptor(descriptor_) {}
            ComponentDescriptorImpl(ComponentDescriptorImpl const &) = delete;
            ComponentDescriptorImpl &operator=(ComponentDescriptorImpl const &) = delete;

            bool isSuperType(ComponentDescriptor const *subType) const override {
                return TypeDescriptor::isSuperType(descriptor, subType->getDescriptor());
            }

            TypeDescriptor const *getDescriptor() const override {
                return descriptor;
            }

            void init(ObjectHandle<Component> const &component) const override {
                if constexpr (SceneInitialisableType<T>) {
                    static_handle_cast<T>(component)->init();
                }
            }

            void update(ObjectHandle<Component> const &component) const override {
                if constexpr (SceneUpdatableType<T>) {
                    static_handle_cast<T>(component)->update();
                }
            }

            void dispose(ObjectHandle<Component> const &component) const override {
                if constexpr (SceneDisposableType<T>) {
                    static_handle_cast<T>(component)->dispose();
                }
            }

            void init(std::unordered_map<std::uint64_t, ObjectHandle<Component>> const &components) const override {
                if constexpr (SceneInitialisableType<T>) {
                    auto copy = components;
                    std::ranges::for_each(copy, [this](auto const &component) {
                       init(component.second);
                    });
                }
            }

            void update(std::unordered_map<std::uint64_t, ObjectHandle<Component>> const &components) const override {
                if constexpr (SceneUpdatableType<T>) {
                    auto copy = components;
                    std::ranges::for_each(copy, [this](auto const &component) {
                       update(component.second);
                    });
                }
            }

            void dispose(std::unordered_map<std::uint64_t, ObjectHandle<Component>> const &components) const override {
                if constexpr (SceneDisposableType<T>) {
                    auto copy = components;
                    std::ranges::for_each(copy, [this](auto const &component) {
                       dispose(component.second);
                    });
                }
            }
        };
}

#endif