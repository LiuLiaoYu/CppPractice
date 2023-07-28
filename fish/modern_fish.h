

// * output
// clang-format off
inline namespace debug {
template <typename T0, typename... T> void print(T0 t0, T... t) { std::cout << t0; if constexpr (sizeof...(t) > 0) std::cout << ' ', print(t...); else std::cout << '\n'; }

#ifdef DEBUG
#define debug(...) std::cout << '[' << #__VA_ARGS__ << "] ", print(__VA_ARGS__)
#else
#define debug(...) 0
#endif
} // clang-format on
