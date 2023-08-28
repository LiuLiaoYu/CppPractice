#pragma once
// c++20
#include <iostream>
#include <concepts>
// #include <utility>
#include <ranges>
#include <string_view>
#include <chrono>

namespace debug {
// overload `operator<<` for `std::ranges::random_access_range` types, like vector, array
auto &operator<<(auto &ostr, std::ranges::random_access_range auto const &arr) {
    ostr << '[' << arr.front();
    for (auto const &i : arr | std::views::drop(1)) ostr << ',' << i;
    return ostr << ']';
}

// variant print
void print(auto t0, auto... t) {
    std::cout << t0;
    if constexpr (sizeof...(t) > 0) std::cout << ' ', print(t...);
    else std::cout << '\n';
}

// template <typename Ostream, typename T, typename U>
// Ostream &operator<<(Ostream &ostr, std::pair<T, U> const &tar) {
// return ostr << tar.first << ": " << tar.second;
// }

void print_with_identity(auto begin, auto end, auto t0, auto... t) {
    std::cout << std::string_view((*begin).begin(), (*begin).end()) << '=' << t0;
    if constexpr (sizeof...(t) > 0) std::cout << "; ", print_with_identity(++begin, end, t...);
    else std::cout << ";\n";
}

void debug_print(std::string_view s, auto... t) {
    auto split_view = s | std::views::split(std::string_view(", "));
    print_with_identity(split_view.begin(), split_view.end(), t...);
}

class Timer {
    std::chrono::high_resolution_clock::time_point start;
    using duration_ratio = std::chrono::duration<double>;

  public:
    Timer() : start(std::chrono::high_resolution_clock::now()) {}
    ~Timer() {
        std::cout << "------\n"
                  << "time elapsed: " << check() << "s\n";
    }
    inline double check() { return std::chrono::duration_cast<duration_ratio>(std::chrono::high_resolution_clock::now() - start).count(); }
};

Timer timer;
} // namespace debug

// #define debug(...) std::cout << '(' << #__VA_ARGS__ << "): ", debug::print(__VA_ARGS__)
#define debug(...) debug::debug_print(#__VA_ARGS__, __VA_ARGS__)
