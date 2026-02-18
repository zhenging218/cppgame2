#include "game.hpp"

#include <iostream>

namespace cppgame {
    void TestComponent::init() {
        transform = getGameObject().getTransform();
    }

    void TestComponent::update() {
        auto dt = cppengine::Time::deltaTime();

        if (cppengine::Input::isKeyDown(cppengine::KeyCode::SPACE)) {
            auto delta = cppengine::Quaternion(cppengine::Vector3{0.f, 0.f, PI * dt});
            auto rotation = transform->getRotation() * delta;
            transform->setRotation(rotation);
        }

        cppengine::Vector3 translation;
        bool moved = false;

        if (cppengine::Input::isKeyDown(cppengine::KeyCode::W)) {
            translation += cppengine::Vector3{0.f, -50.f * dt, 0.f};
            moved = true;
        }

        if (cppengine::Input::isKeyDown(cppengine::KeyCode::A)) {
            translation += cppengine::Vector3{-50.f * dt, 0.f, 0.f};
            moved = true;
        }

        if (cppengine::Input::isKeyDown(cppengine::KeyCode::S)) {
            translation += cppengine::Vector3{0.f, 50.f * dt, 0.f};

            moved = true;
        }

        if (cppengine::Input::isKeyDown(cppengine::KeyCode::D)) {
            translation += cppengine::Vector3{50.f * dt, 0.f, 0.f};
            moved = true;
        }

        if (moved) {
            transform->setPosition(transform->getPosition() + translation);
        }

    }

    void TestComponent::teardown() {
        std::cout << "teardown called\n";
    }
}
