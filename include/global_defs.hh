#ifndef INCLUDE_GLOBAL_DEFS_HH_
#define INCLUDE_GLOBAL_DEFS_HH_

#ifndef __SUN_N__
#define __SUN_N__ 3
#endif

constexpr int SUN_N = __SUN_N__;
constexpr int SUN_elems = 2 * SUN_N * SUN_N;
constexpr int SUN_dim = SUN_N * SUN_N - 1;

#endif
