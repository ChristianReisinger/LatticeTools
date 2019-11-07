#include <set>

#include <heatbath.hh>
#include <io.hh>

#include <MCSU2Interface.hh>

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

void MCSU2Interface::do_sweep(double* const config_buf, int T, int L, double beta, const std::set<int>& fixed_timeslices) const {
	::do_sweep(config_buf, T, L, beta, fixed_timeslices);
}

void MCSU2Interface::write_gauge_field(const double* const config_buf, const std::string& config_filename, int T, int L,
		const std::string& header) const {
	::write_gauge_field(config_buf, config_filename.c_str(), T, L, header.c_str());
}

void MCSU2Interface::read_gauge_field(double* const config_buf, const std::string& config_filename, int T, int L) const {
	::read_gauge_field(config_buf, config_filename.c_str(), T, L);
}

}
}
}
