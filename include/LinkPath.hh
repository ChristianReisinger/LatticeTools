#include <array>
#include <global_defs.hh>

#ifndef INCLUDE_LINKPATH_HH_
#define INCLUDE_LINKPATH_HH_

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

class LinkPath {

public:
	double path[SUN_elems];

	LinkPath(const double* gauge_field, int T, int L, const std::array<int, 4>& n);

	LinkPath& operator()(int mu, bool pos);
	LinkPath& move(int mu, int dist);
	LinkPath& reset(const std::array<int, 4>& new_n);

private:
	const double* gauge_field;
	int T, L;
	std::array<int, 4> n;
};

}
}
}

#endif /* INCLUDE_LINKPATH_HH_ */
