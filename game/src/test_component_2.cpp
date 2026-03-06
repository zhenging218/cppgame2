#include "game.hpp"

namespace cppgame {
    void TestComponent2::init() {
        transform = getGameObject().getTransform();
    }

    void TestComponent2::update() {
        auto dt = Time::deltaTime();

        if (Input::isKeyDown(KeyCode::LEFT_ARROW)) {
            auto delta = Quaternion(Vector3{0.f, 0.f, static_cast<float>(std::numbers::pi * dt)});
            auto rotation = transform->getRotation() * delta;
            transform->setRotation(rotation);
        }

        Vector3 scale;
        bool scaled = false;

        if (Input::isKeyDown(KeyCode::UP_ARROW)) {
            scale += Vector3(50.f * dt, 50.f * dt, 0);
            scaled = true;
        }

        if (Input::isKeyDown(KeyCode::DOWN_ARROW)) {
            scale += Vector3(-50.f * dt, -50.f * dt, 0);
            scaled = true;
        }

        if (scaled) {
            transform->setScale(transform->getScale() + Vector3{scale.x, scale.y, 1.f});
        }

    }
}