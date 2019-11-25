#include <set>
#include <memory>
#include <string>

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

#include <SUNGaugefield.hh>

#ifndef INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_CL2QCDGAUGEFIELD_HH_
#define INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_CL2QCDGAUGEFIELD_HH_

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

class CL2QCDGaugefield: public SUNGaugefield {
public:
	CL2QCDGaugefield(int T, int L, int seed, double beta, int overrelax_steps, std::string filename);
	CL2QCDGaugefield(const CL2QCDGaugefield&) = delete;
	CL2QCDGaugefield(CL2QCDGaugefield&&) = delete;
	CL2QCDGaugefield& operator=(const CL2QCDGaugefield&) = delete;
	CL2QCDGaugefield& operator=(CL2QCDGaugefield&&) = delete;
	~CL2QCDGaugefield();

	void do_sweep(const std::set<int>& fixed_timeslices = std::set<int>()) override;
	void set(const double* gauge_field) override;
	void read(const std::string& config_filename) override;

	void write(const std::string& config_filename) const override;
	int get_T() const override;
	int get_L() const override;
	double get_beta() const override;
	const double* get() override;

private:
	void free_buf();

	const int m_overrelax_steps;

	std::unique_ptr<meta::Inputparameters> m_params;
	std::unique_ptr<const hardware::HardwareParametersInterface> m_hardware_params;
	std::unique_ptr<const hardware::code::OpenClKernelParametersInterface> m_kernel_params;
	std::unique_ptr<physics::PrngParametersInterface> m_prng_params;
	std::unique_ptr<hardware::System> m_system;
	std::unique_ptr<physics::PRNG> m_prng;

	std::unique_ptr<physics::InterfacesHandler> m_interfaces_handler;

	std::unique_ptr<physics::lattices::Gaugefield> m_gaugefield;
	double* m_contractioncode_gaugefield_buf = nullptr;
};

}
}
}

#endif
