//
// Created by Admin on 31/10/2026.
//

#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#include "memory/object_handle.hpp"

namespace cppengine {
    class ComponentManager {
    private:

    public:

        template <typename T, typename ... Args>
        ObjectHandle<T> createComponent(Args &&... args);
    };
}

#endif //COMPONENT_MANAGER_HPP
