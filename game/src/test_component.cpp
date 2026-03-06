#include "game.hpp"

#include <iostream>

#include <numbers>
#include <cmath>

namespace cppgame {
    using namespace cppengine;
    
    void TestComponent::init() {
        transform = getGameObject().getTransform();
    }

    void TestComponent::update() {
        auto dt = Time::deltaTime();

        if (Input::isKeyDown(KeyCode::SPACE)) {
            auto delta = Quaternion(Vector3{0.f, 0.f, static_cast<float>(std::numbers::pi * dt)});
            auto rotation = transform->getRotation() * delta;
            transform->setRotation(rotation);
        }

        Vector3 translation;
        Vector3 scale;
        bool moved = false;
        bool scaled = false;

        if (Input::isKeyDown(KeyCode::W)) {
            translation += Vector3{0.f, -50.f * dt, 0.f};
            moved = true;
        }

        if (Input::isKeyDown(KeyCode::A)) {
            translation += Vector3{-50.f * dt, 0.f, 0.f};
            moved = true;
        }

        if (Input::isKeyDown(KeyCode::S)) {
            translation += Vector3{0.f, 50.f * dt, 0.f};

            moved = true;
        }

        if (Input::isKeyDown(KeyCode::D)) {
            translation += Vector3{50.f * dt, 0.f, 0.f};
            moved = true;
        }

        if (Input::isKeyDown(KeyCode::E)) {
            scale += Vector3(50.f * dt, 50.f * dt, 0);
            scaled = true;
        }

        if (Input::isKeyDown(KeyCode::Q)) {
            scale += Vector3(-50.f * dt, -50.f * dt, 0);
            scaled = true;
        }

        if (moved) {
            transform->setPosition(transform->getPosition() + translation);
        }

        if (scaled) {
            transform->setScale(transform->getScale() + Vector3{scale.x, scale.y, 1.f});
        }

    }
}
