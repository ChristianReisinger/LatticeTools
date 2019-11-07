#include <string>
#include <stdexcept>

#include <physics/algorithms/su3heatbath.hpp>

#include <CL2QCDInterface.hh>

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

CL2QCDInterface::CL2QCDInterface(int T, int L, int seed, int overrelax_steps) :
		m_params(std::string("")
				+ " --useGPU 0"
				+ " --nSpace " + L
				+ " --nTime " + T
				+ " --hostSeed " + seed,
				5, "su3heatbath"), m_overrelax_steps(overrelax_steps) {

	m_prng_params = new physics::PrngParametersImplementation(m_params);

	m_hardware_params = new hardware::HardwareParametersImplementation(&m_params);
	m_kernel_params = new hardware::code::OpenClKernelParametersImplementation(m_params);
	m_system = new hardware::System(*m_hardware_params, *m_kernel_params);

	m_prng = new physics::PRNG(*m_system, m_prng_params);

	m_interfaces_handler = std::unique_ptr<physics::InterfacesHandler>(
			new physics::InterfacesHandlerImplementation { m_params });

	m_gaugefield = new physics::lattices::Gaugefield(*m_system,
			&(m_interfaces_handler->getInterface<physics::lattices::Gaugefield>()),
			*m_prng);
}

void CL2QCDInterface::do_sweep(double* const config_buf, int T, int L, double beta, const std::set<int>& fixed_timeslices) const {
	if(T != m_gaugefield->getParameters()->getNt() || L != m_gaugefield->getParameters()->getNs()
			|| m_gaugefield->getParameters()->getBeta() != beta)
		throw std::invalid_argument("CL2QCDInterface::do_sweep invalid T / L / beta");

	physics::algorithms::su3heatbath(*m_gaugefield, *m_prng, m_overrelax_steps, fixed_timeslices);

	m_gaugefield->copyGaugefieldToContractionCodeArray(config_buf);
}

}
}
}
