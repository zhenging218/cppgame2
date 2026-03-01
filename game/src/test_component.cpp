#include "game.hpp"

#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>

namespace cppgame {
    using namespace cppengine;
    
    void TestComponent::init() {
        transform = getGameObject().getTransform();
    }

    void TestComponent::update() {
        auto dt = Time::deltaTime();

        if (Input::isKeyDown(KeyCode::SPACE)) {
            auto delta = Quaternion(Vector3{0.f, 0.f, static_cast<float>(M_PI * dt)});
            auto rotation = transform->getRotation() * delta;
            transform->setRotation(rotation);
        }

        Vector3 translation;
        bool moved = false;

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

        if (moved) {
            transform->setPosition(transform->getPosition() + translation);
        }

    }
}
