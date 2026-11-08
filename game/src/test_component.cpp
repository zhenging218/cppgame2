#include "game.hpp"

#include <iostream>

#include <numbers>
#include <cmath>
#include <set>

namespace {
    struct Test {
        int x = 0;
        std::string y = "hello";
        int z[10] {0};
        std::map<std::string, float> w { {"hi", 0.5f}, {"yo", 1.3f} };
        std::set<int> u { 69, 420 };
        std::unordered_map<int, std::string> v { { 67, "hihi" }, { 1337, "bye" } };

    private:
        int i = 555;

    public:
        int const &getI() const { return i; }
        void setI(int const &i_) { i = i_; }
    };
}

DECL_TYPE_DESCRIPTOR(Test);

DECL_TYPE_MEMBERS(Test)
    DECL_TYPE_MEMBER_FIELD(x),
    DECL_TYPE_MEMBER_FIELD(y),
    DECL_TYPE_MEMBER_FIELD(z),
    DECL_TYPE_MEMBER_FIELD(w),
    DECL_TYPE_MEMBER_FIELD(u),
    DECL_TYPE_MEMBER_FIELD(v),
    DECL_TYPE_MEMBER_ACCESSORS(i, getI, setI)
END_DECL_TYPE_MEMBERS();

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

        std::cout << Test{} << std::endl;
    }
}
