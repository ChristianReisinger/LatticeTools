#include <set>

#include <heatbath.hh>

#include <MCSU2Interface.hh>

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

void MCSU2Interface::do_sweep(double* const config_buf, int T, int L, double beta, const std::set<int>& fixed_timeslices) const {
	::do_sweep(config_buf, T, L, beta, fixed_timeslices);
}

}
}
}
