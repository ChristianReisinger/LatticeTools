#include <string>
#include <stdexcept>
#include <memory>

#include <helper_functions.hh>
#include <meta/inputparameters.hpp>
#include <hardware/hardwareParameters.hpp>
#include <hardware/openClKernelParameters.hpp>
#include <hardware/system.hpp>
#include <physics/interfacesHandler.hpp>
#include <physics/prngInterface.hpp>
#include <physics/lattices/gaugefield.hpp>
#include <physics/algorithms/su3heatbath.hpp>
#include <physics/prng.hpp>
#include <interfaceImplementations/physicsParameters.hpp>
#include <interfaceImplementations/hardwareParameters.hpp>
#include <interfaceImplementations/openClKernelParameters.hpp>
#include <interfaceImplementations/interfacesHandler.hpp>

#include <CL2QCDInterface.hh>

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

class CL2QCDInterface::Implementation {
public:
	Implementation(int T, int L, int seed, double beta, int overrelax_steps) :
			m_overrelax_steps(overrelax_steps) {
		using tools::helper::make_unique;

		const char* params_argv[] = { "dummy_bin_path",
				"--useGPU", "0",
				"--nSpace", std::to_string(L).c_str(),
				"--nTime", std::to_string(T).c_str(),
				"--hostSeed", std::to_string(seed).c_str(),
				"--beta", std::to_string(beta).c_str()
		};
		m_params = make_unique<meta::Inputparameters>(11, params_argv, "su3heatbath");

		m_prng_params = make_unique<physics::PrngParametersImplementation>(*m_params);

		m_hardware_params = make_unique<hardware::HardwareParametersImplementation>(m_params.get());
		m_kernel_params = make_unique<hardware::code::OpenClKernelParametersImplementation>(*m_params);
		m_system = make_unique<hardware::System>(*m_hardware_params, *m_kernel_params);

		m_prng = make_unique<physics::PRNG>(*m_system, m_prng_params.get());

		m_interfaces_handler = make_unique<physics::InterfacesHandlerImplementation>(*m_params);

		gaugefield = make_unique<physics::lattices::Gaugefield>(*m_system,
				&(m_interfaces_handler->getInterface<physics::lattices::Gaugefield>()),
				*m_prng);

	}

	void do_sweep(double* config_buf, const std::set<int>& fixed_timeslices) const {
		physics::algorithms::su3heatbath(*gaugefield, *m_prng, m_overrelax_steps, fixed_timeslices);
		gaugefield->copyGaugefieldToContractionCodeArray(config_buf);
	}

	std::unique_ptr<physics::lattices::Gaugefield> gaugefield;

private:
	const int m_overrelax_steps;

	std::unique_ptr<meta::Inputparameters> m_params;
	std::unique_ptr<const hardware::HardwareParametersInterface> m_hardware_params;
	std::unique_ptr<const hardware::code::OpenClKernelParametersInterface> m_kernel_params;
	std::unique_ptr<physics::PrngParametersInterface> m_prng_params;
	std::unique_ptr<hardware::System> m_system;
	std::unique_ptr<physics::PRNG> m_prng;

	std::unique_ptr<physics::InterfacesHandler> m_interfaces_handler;
};

CL2QCDInterface::CL2QCDInterface(int T, int L, int seed, double beta, int overrelax_steps) :
		impl { tools::helper::make_unique<Implementation>(T, L, beta, overrelax_steps) } {
}

void CL2QCDInterface::do_sweep(double* config_buf, const std::set<int>& fixed_timeslices) const {
	impl->do_sweep(config_buf, fixed_timeslices);
}

void CL2QCDInterface::write_gauge_field(const double* config_buf, const std::string& config_filename,
		const std::string& header) const {
	throw std::logic_error("CL2QCDInterface::write_gauge_field not implemented");
}

void CL2QCDInterface::read_gauge_field(double* config_buf, const std::string& config_filename) const {
	throw std::logic_error("CL2QCDInterface::read_gauge_field not implemented");
}

int CL2QCDInterface::get_T() const {
	return impl->gaugefield->getParameters()->getNt();
}
int CL2QCDInterface::get_L() const {
	return impl->gaugefield->getParameters()->getNs();
}
double CL2QCDInterface::get_beta() const {
	return impl->gaugefield->getParameters()->getBeta();
}

}
}
}
