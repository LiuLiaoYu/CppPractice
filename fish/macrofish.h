#pragma once

// short typename
using byte = unsigned char;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;

// low level typename
using i8 = char;
using u8 = unsigned char;

using i16 = short;
using u16 = unsigned short;

using i32 = int;
using u32 = unsigned int;

using i64 = long long;
using u64 = unsigned long long;

// for abbr.
#define loop(i, n) for (int i = 0; i < n; i++)
#define rloop(i, n) for (int i = n - 1; i >= 0; i--)
#define looplr(i, l, r) for (int i = l; i < r; i++)
#define looprl(i, r, l) for (int i = r - 1; i >= l; i--)

/* another style
#define loop0(var, n) for (int var = 0; var < (n); var++)
#define loop1(var, n) for (int var = 1; var <= (n); var++)
// #define loop(var, begin, end) for (decltype(end) var = begin; var < end; ++var)
*/

/* decltype, few used
#define loop(i, n) for (decltype(n) i = 0; i < n; i++)
*/

#define forall(var, array) for (auto var : array)

#define in_range(v, l, r) (((v) >= (l)) && ((v) < (r)))
#define in_range_cc(v, l, r) (((v) >= (l)) && ((v) <= (r)))

/* not recommond
// if statement could declare a temp variable in it's condition area, like below
// if (int a = 1; a) do_some_thing();
// since if statement only execute once, it doesn't matter that the temp variable would cost efficience
// but while statement doesn't have this similar surgar, although you can use a varible declaration as a condition, but it will execute in every loop
// and for statement can declare once before loop block
// so come the fish below

#define loopon(temp, stat) for (auto temp = (stat); temp; temp = (stat))
#define whileon(stat) for (auto _ = (stat); _; _ = stat)

#define REF const &
#define Ref auto const &

// operation
// clang-format offgit
#define modulo(x, op, y, p) ((((x % p) op(y % p)) % p + p) % p)
// #define modulo(x, op, y, p) (( ( ((x)%(p)) op ((y)%(p)) ) % (p) + (p) ) % (p))
// clang-format on

*/

// Semantic
// #define
