/*
 * LinkPath.cc
 *
 *  Created on: 31 Jul 2019
 *      Author: reisinger
 */

#include <array>
#include <global_defs.hh>

class LinkPath {

public:

	double path[SUN_elems];

	LinkPath(double* gauge_field, int T, int L, const std::array<int, 4>& n);

	LinkPath& operator()(int mu, bool pos);
	LinkPath& move(int mu, int dist);
	LinkPath& reset(const std::array<int, 4>& new_n);

private:
	double* gauge_field;
	int T, L;
	std::array<int, 4> n;
};
