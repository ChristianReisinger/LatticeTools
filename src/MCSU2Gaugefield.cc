#include <set>

#include <heatbath.hh>
#include <io.hh>
#include <ranlux.hh>

#include <global_defs.hh>

#include <MCSU2Gaugefield.hh>

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

MCSU2Gaugefield::MCSU2Gaugefield(int T, int L, int seed, double beta) :
		m_T(T), m_L(L), m_beta(beta) {
	InitializeRand(seed);
	Gauge_Field_Alloc(m_gaugefield_buf, T, L);
}

MCSU2Gaugefield::~MCSU2Gaugefield() {
	Gauge_Field_Free(m_gaugefield_buf);
}

void MCSU2Gaugefield::do_sweep(const std::set<int>& fixed_timeslices) const {
	::do_sweep(m_gaugefield_buf, m_T, m_L, m_beta, fixed_timeslices);
}

void MCSU2Gaugefield::write(const std::string& config_filename, const std::string& header) const {
	::write_gauge_field(m_gaugefield_buf, config_filename.c_str(), m_T, m_L, header.c_str());
}

void MCSU2Gaugefield::read(const std::string& config_filename) const {
	::read_gauge_field(m_gaugefield_buf, config_filename.c_str(), m_T, m_L);
}

int MCSU2Gaugefield::get_T() const {
	return m_T;
}
int MCSU2Gaugefield::get_L() const {
	return m_L;
}
double MCSU2Gaugefield::get_beta() const {
	return m_beta;
}

const double* MCSU2Gaugefield::get_buffer() const {
	return m_gaugefield_buf;
}

}
}
}
