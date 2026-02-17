#include "game.hpp"

#include <iostream>

namespace cppgame {
    void TestComponent::update() {
        std::cout << "updating with dt = " << cppengine::Time::deltaTime() << "\n";
    }
}
