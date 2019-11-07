#include <set>
#include <memory>

#include <meta/inputparameters.hpp>
#include <interfaceImplementations/hardwareParameters.hpp>
#include <interfaceImplementations/openClKernelParameters.hpp>
#include <hardware/system.hpp>
#include <interfaceImplementations/interfacesHandler.hpp>
#include <physics/prng.hpp>
#include <physics/lattices/gaugefield.hpp>

#include <HeatbathInterface.hh>

#ifndef INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_CL2QCDINTERFACE_HH_
#define INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_CL2QCDINTERFACE_HH_

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

class CL2QCDInterface: public HeatbathInterface {
public:
	CL2QCDInterface(int T, int L, int seed, int overrelax_steps);
	CL2QCDInterface(const CL2QCDInterface&) = delete;
	CL2QCDInterface(CL2QCDInterface&&) = delete;
	CL2QCDInterface& operator=(const CL2QCDInterface&) = delete;
	CL2QCDInterface& operator=(CL2QCDInterface&&) = delete;

	void do_sweep(double* const config_buf, int T, int L, double beta,
			const std::set<int>& fixed_timeslices = std::set<int>()) const override;

private:
	const int m_overrelax_steps;

	meta::Inputparameters m_params;
	std::unique_ptr<const hardware::HardwareParametersImplementation> m_hardware_params;
	std::unique_ptr<const hardware::code::OpenClKernelParametersImplementation> m_kernel_params;
	std::unique_ptr<physics::PrngParametersImplementation> m_prng_params;
	std::unique_ptr<hardware::System> m_system;
	std::unique_ptr<physics::PRNG> m_prng;

	std::unique_ptr<physics::InterfacesHandler> m_interfaces_handler;
	std::unique_ptr<physics::lattices::Gaugefield> m_gaugefield;
};

}
}
}
