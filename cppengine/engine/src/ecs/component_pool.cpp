//
// Created by Admin on 31/10/2026.
//

#include "ecs/component_pool.hpp"

namespace cppengine {
    void ComponentPoolDelegate::operator()(Component &component) const {
        invoker(delegate, component);
    }

    ComponentPool::~ComponentPool() = default;
}
