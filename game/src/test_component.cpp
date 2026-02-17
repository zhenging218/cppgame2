#include "game.hpp"

#include <iostream>

namespace cppgame {
    void TestComponent::init() {
        std::cout << "init called\n";
    }

    void TestComponent::update() {

    }

    void TestComponent::teardown() {
        std::cout << "teardown called\n";
    }
}
