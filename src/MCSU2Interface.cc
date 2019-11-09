#include <set>

#include <heatbath.hh>
#include <io.hh>
#include <ranlux.hh>

#include <MCSU2Interface.hh>

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

MCSU2Interface::MCSU2Interface(int T, int L, int seed, double beta) : m_T(T), m_L(L), m_beta(beta) {
	InitializeRand(seed);
}

void MCSU2Interface::do_sweep(double* config_buf, const std::set<int>& fixed_timeslices) const {
	::do_sweep(config_buf, m_T, m_L, m_beta, fixed_timeslices);
}

void MCSU2Interface::write_gauge_field(const double* config_buf, const std::string& config_filename,
		const std::string& header) const {
	::write_gauge_field(config_buf, config_filename.c_str(), m_T, m_L, header.c_str());
}

void MCSU2Interface::read_gauge_field(double* config_buf, const std::string& config_filename) const {
	::read_gauge_field(config_buf, config_filename.c_str(), m_T, m_L);
}

int MCSU2Interface::get_T() const {
	return m_T;
}
int MCSU2Interface::get_L() const {
	return m_L;
}
double MCSU2Interface::get_beta() const {
	return m_beta;
}

}
}
}
