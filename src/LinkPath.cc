#include <LinkPath.hh>

#include <array>

#include <global_defs.hh>
#include <geometry.hh>
#include <geometry2.hh>

#include <linear_algebra.hh>

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

LinkPath::LinkPath(const double* gauge_field, int T, int L, const std::array<int, N_dim>& n) :
		gauge_field(gauge_field), T(T), L(L), n(n) {
	cm_eq_id(path);
}

LinkPath& LinkPath::operator()(int mu, bool pos) {
	double U[SUN_elems];
	cm_eq_cm(U, path);
	if (pos) {
		cm_eq_cm_ti_cm(path, U, gauge_field + ggi_n(n[0], n[1], n[2], n[3], N_dim, mu, T, L));
		n[mu]++;
	} else {
		n[mu]--;
		cm_eq_cm_ti_cm_dag(path, U, gauge_field + ggi_n(n[0], n[1], n[2], n[3], N_dim, mu, T, L));
	}
	return *this;
}

LinkPath& LinkPath::move(int mu, int dist) {
	n[mu] += dist;
	return *this;
}

LinkPath& LinkPath::reset(const std::array<int, N_dim>& new_n) {
	n = new_n;
	cm_eq_id(path);
	return *this;
}

}
}
}
