#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

namespace cppengine {
    class Time {
    public:

        using frame_time_type = decltype(std::chrono::high_resolution_clock::now());
        using delta_time_type = float;
        using frame_duration_type = std::chrono::duration<delta_time_type>;
        using time_difference_type = decltype(std::declval<frame_duration_type const &>() - std::declval<frame_duration_type const &>());

        static delta_time_type deltaTime();

        static Time &getInstance();

        void reset();
        void advance();

        Time();
        Time(Time const &) = delete;
        Time(Time &&) noexcept = delete;
        Time &operator=(Time const &) = delete;
        Time &operator=(Time &&) noexcept = delete;

    private:
        frame_time_type before;
        delta_time_type dt;
    };
}

#endif