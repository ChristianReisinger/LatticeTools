#include <stdexcept>

#include <io.hh>

#include <global_defs.hh>

#include <ContractionCodeGaugefield.hh>

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

ContractionCodeGaugefield::ContractionCodeGaugefield(int T, int L, std::string filename) :
		m_L { L }, m_T { T } {
	Gauge_Field_Alloc(m_gaugefield_buf, T, L);
	read(filename);
}

ContractionCodeGaugefield::~ContractionCodeGaugefield() {
	Gauge_Field_Free(m_gaugefield_buf);
}

void ContractionCodeGaugefield::do_sweep(const std::set<int>&) {
	throw std::runtime_error("ContractionCodeGaugefield::do_sweep not supported");
}

void ContractionCodeGaugefield::set(const double* gauge_field) {
	Gauge_Field_Copy(m_gaugefield_buf, gauge_field, m_T, m_L);
}

void ContractionCodeGaugefield::read(const std::string& config_filename) {
	::read_gauge_field(m_gaugefield_buf, config_filename.c_str(), m_T, m_L);
}

void ContractionCodeGaugefield::write(const std::string& config_filename) const {
	throw std::runtime_error("ContractionCodeGaugefield::write not implemented");
}

int ContractionCodeGaugefield::get_T() const {
	return m_T;
}
int ContractionCodeGaugefield::get_L() const {
	return m_L;
}
double ContractionCodeGaugefield::get_beta() const {
	throw std::runtime_error("ContractionCodeGaugefield has no beta member");
}

const double* ContractionCodeGaugefield::get() const {
	return m_gaugefield_buf;
}

}
}
}
