#pragma once

// * simplify base typename (conventional)
using byte = unsigned char;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;

// * simplify base typename (low level)
using i8 = char;
using u8 = unsigned char;

using i16 = short;
using u16 = unsigned short;

using i32 = int;
using u32 = unsigned int;

using i64 = long long;
using u64 = unsigned long long;

// * for abbr.
#define loop(i, n) for (int i = 0; i < n; i++)
#define rloop(i, n) for (int i = n - 1; i >= 0; i--)
#define looplr(i, l, r) for (int i = l; i < r; i++)
#define looprl(i, l, r) for (int i = r - 1; i >= l; i--)

/* another style
#define loop0(var, n) for (int var = 0; var < (n); var++)
#define loop1(var, n) for (int var = 1; var <= (n); var++)
// #define loop(var, begin, end) for (decltype(end) var = begin; var < end; ++var)
*/

/* decltype, few used
#define loop(i, n) for (decltype(n) i = 0; i < n; i++)
*/

// #define forall(var, array) for (auto var : array)

// * conditions often occur
#define in_range(v, l, r) (((v) >= (l)) && ((v) < (r)))
#define in_range_cc(v, l, r) (((v) >= (l)) && ((v) <= (r)))

// * simplify `const &`
#define crf const &
// usage: `auto fun(auto crf arr) -> void;`
#define cref auto const &

// other style
// #define REF const &
// #define Ref auto const &
// #define cref const &

// * like `fn` & `let`
#define fn auto
#define let auto

// * parameter macro
#define range(left_value) left_value.begin(), left_value.end()

// * debug

// ! below are NOT recommended
// module an epression like `a + b`
#define modulo(x, op, y, p) ((((x % p) op(y % p)) % p + p) % p)
// usage: `module(173, +, 245, 128)`

// if statement could declare a temp variable in it's condition area, like below
// if (int a = 1; a) do_some_thing();
// since if statement only execute once, it doesn't matter that the temp variable would cost efficience
// but while statement doesn't have this similar surgar, although you can use a varible declaration as a condition, but it will execute in every loop
// and for statement can declare once before loop block
// so come the fish below

#define whileon(stat) for (auto _ = (stat); _; _ = stat)
#define loopon(temp, stat) for (auto temp = (stat); temp; temp = (stat))
