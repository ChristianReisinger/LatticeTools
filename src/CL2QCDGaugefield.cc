#include <string>
#include <stdexcept>
#include <memory>

#include <helper_functions.hh>

#include <global_defs.hh>

#include <CL2QCDGaugefield.hh>

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

CL2QCDGaugefield::CL2QCDGaugefield(int T, int L, int seed, double beta, int overrelax_steps, std::string filename) :
		m_overrelax_steps(overrelax_steps) {
	using tools::helper::make_unique;

	const char* params_argv[] = { "dummy_bin_path",
			"--useGPU", "0",
			"--nSpace", std::to_string(L).c_str(),
			"--nTime", std::to_string(T).c_str(),
			"--hostSeed", std::to_string(seed).c_str(),
			"--beta", std::to_string(beta).c_str(),
			"--startCondition", "continue",
			"--initialConf", filename.c_str()
	};
	m_params = make_unique<meta::Inputparameters>(15, params_argv, "su3heatbath");

	m_prng_params = make_unique<physics::PrngParametersImplementation>(*m_params);

	m_hardware_params = make_unique<hardware::HardwareParametersImplementation>(m_params.get());
	m_kernel_params = make_unique<hardware::code::OpenClKernelParametersImplementation>(*m_params);
	m_system = make_unique<hardware::System>(*m_hardware_params, *m_kernel_params);

	m_prng = make_unique<physics::PRNG>(*m_system, m_prng_params.get());

	m_interfaces_handler = make_unique<physics::InterfacesHandlerImplementation>(*m_params);

	m_gaugefield = make_unique<physics::lattices::Gaugefield>(*m_system,
			&(m_interfaces_handler->getInterface<physics::lattices::Gaugefield>()),
			*m_prng);

}

CL2QCDGaugefield::~CL2QCDGaugefield() {
	free_buf();
}

void CL2QCDGaugefield::do_sweep(const std::set<int>& fixed_timeslices) {
	free_buf();
	physics::algorithms::su3heatbath(*m_gaugefield, *m_prng, m_overrelax_steps, fixed_timeslices);
}

void CL2QCDGaugefield::set(const double* gauge_field) {
	free_buf();
	m_gaugefield->setToContractionCodeArray(gauge_field);
}

void CL2QCDGaugefield::read(const std::string& config_filename) {
	free_buf();
	m_gaugefield->readFromILDGSourcefile(config_filename);
}

void CL2QCDGaugefield::write(const std::string& config_filename) const {
	m_gaugefield->save(config_filename, 0);
}

int CL2QCDGaugefield::get_T() const {
	return m_gaugefield->getParameters()->getNt();
}
int CL2QCDGaugefield::get_L() const {
	return m_gaugefield->getParameters()->getNs();
}
double CL2QCDGaugefield::get_beta() const {
	return m_gaugefield->getParameters()->getBeta();
}

const double* CL2QCDGaugefield::get() {
	if (m_contractioncode_gaugefield_buf == nullptr) {
		Gauge_Field_Alloc(m_contractioncode_gaugefield_buf, get_T(), get_L());
		m_gaugefield->copyToContractionCodeArray(m_contractioncode_gaugefield_buf);
	}
	return m_contractioncode_gaugefield_buf;
}

void CL2QCDGaugefield::free_buf() {
	if (m_contractioncode_gaugefield_buf != nullptr) {
		Gauge_Field_Free(m_contractioncode_gaugefield_buf);
		m_contractioncode_gaugefield_buf = nullptr;
	}
}

}
}
}
