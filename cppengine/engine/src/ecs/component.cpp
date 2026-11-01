//
// Created by Admin on 31/10/2026.
//

#include "ecs/ecs.hpp"

namespace cppengine {
    std::uint64_t Component::getStamp() const {
        return stamp;
    }

    ComponentState Component::getState() const {
        return state;
    }

    std::uint64_t Component::getOwner() const {
        return owner;
    }

    void Component::setOwner(std::uint64_t newOwner) {
        owner = newOwner;
    }

    void Component::setStamp(std::uint64_t newStamp) {
        stamp = newStamp;
    }

    void Component::setState(ComponentState newState) {
        state = newState;
    }

    Component::~Component() = default;
}
