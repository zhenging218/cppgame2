#include "engine.hpp"

namespace cppengine {
    Time::Time() : before(std::chrono::high_resolution_clock::now()), dt(0.f) {

    }

    Time::delta_time_type Time::deltaTime() {
        return getInstance().dt;
    }

    void Time::advance() {
        auto now = std::chrono::high_resolution_clock::now();
        time_difference_type timeTaken = now - before;
        dt = timeTaken.count();
        before = now;
    }

    Time &Time::getInstance() {
        static Time instance;
        return instance;
    }
}
