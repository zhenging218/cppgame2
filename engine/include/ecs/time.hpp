#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

namespace cppengine {
    class Time {
    private:

    public:

        using frame_time_type = std::chrono::time_point<std::chrono::high_resolution_clock>;
        using delta_time_type = double;
        using frame_duration_type = std::chrono::duration<delta_time_type>;
        using time_difference_type = decltype(std::declval<frame_duration_type const &>() - std::declval<frame_duration_type const &>());

        static delta_time_type deltaTime();

        static Time &getInstance();

        Time();
        Time(Time const &) = delete;
        Time(Time &&) noexcept = delete;
        Time &operator=(Time const &) = delete;
        Time &operator=(Time &&) noexcept = delete;
    };
}

#endif