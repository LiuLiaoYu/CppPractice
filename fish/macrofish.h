#pragma once

// short typename
typedef long long ll;
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long long ull;

// low level typename
typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// loops

#define loop0(var, n) for (int var = 0; var < (n); var++)
#define loop1(var, n) for (int var = 1; var <= (n); var++)

#define loop(var, begin, end) for (decltype(end) var = begin; var < end; ++var)

#define forall(var, array) for (auto var : array)

#define REF const &
#define Ref auto const &

// operation
// clang-format off
#define modulo(x, op, y, p) ((((x % p) op (y % p)) % p + p) % p)
// #define modulo(x, op, y, p) (( ( ((x)%(p)) op ((y)%(p)) ) % (p) + (p) ) % (p))
// clang-format on


// Semantic
// #define