#include <algorithm>

#ifndef INCLUDE_GLOBAL_DEFS_HH_
#define INCLUDE_GLOBAL_DEFS_HH_

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

#ifndef __SUN_N__
#define __SUN_N__ 3
#endif

constexpr int SUN_N = __SUN_N__;
constexpr int SUN_elems = 2 * SUN_N * SUN_N;
constexpr int SUN_dim = SUN_N * SUN_N - 1;
constexpr int N_dim = 4;

inline void Gauge_Field_Alloc(double*& gauge_field, int T, int L) {
	gauge_field = new double[T * L * L * L * N_dim * SUN_elems];
}

inline void Gauge_Field_Free(double*& gauge_field) {
	delete[] gauge_field;
}

inline void Gauge_Field_Copy(double* dest, const double* src, int T, int L) {
	std::copy(src, src + T * L * L * L * N_dim * SUN_elems, dest);
}

}
}
}

#endif
