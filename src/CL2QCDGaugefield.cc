#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <chrono>
#include <iostream>

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

#include <global_defs.hh>

#include <CL2QCDGaugefield.hh>

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

class CL2QCDGaugefield::Implementation {
private:
	void free_buf() {
		if (m_contractioncode_gaugefield_buf != nullptr) {
			Gauge_Field_Free(m_contractioncode_gaugefield_buf);
			m_contractioncode_gaugefield_buf = nullptr;
		}
	}

	void print_time_spent() const {
		std::cout << "Time spent in CL2QCDGaugefield:\n";
		const std::map<std::string, const std::chrono::steady_clock::duration*> measured_times = {
				{ "reading", &m_time_spent_reading },
				{ "writing", &m_time_spent_writing },
				{ "converting", &m_time_spent_converting },
				{ "sweeping", &m_time_spent_sweeping }
		};
		for (const auto& name_time : measured_times)
			std::cout << "\t" << name_time.first << ":\t"
					<< std::chrono::duration_cast<std::chrono::seconds>(*(name_time.second)).count() << "\n";
	}

public:
	Implementation(int T, int L, int seed, double beta, int overrelax_steps, std::string filename) :
			m_overrelax_steps(overrelax_steps) {
		using tools::helper::make_unique;

		const std::vector<std::string> params_args = { "dummy_bin_path",
				"--useGPU", "0",
				"--nSpace", std::to_string(L),
				"--nTime", std::to_string(T),
				"--hostSeed", std::to_string(seed),
				"--beta", std::to_string(beta),
				"--startCondition", "continue",
				"--initialConf", filename,
				"--logLevel", "ERROR"
		};
		std::vector<const char*> params_argv;
		for (const auto& arg : params_args)
			params_argv.push_back(arg.data());
		m_params = make_unique<meta::Inputparameters>(params_argv.size(), params_argv.data(), "su3heatbath");

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

	~Implementation() {
		free_buf();
		print_time_spent();
	}

	void do_sweep(const std::set<int>& fixed_timeslices) {
		auto start_time = std::chrono::steady_clock::now();
		free_buf();
		physics::algorithms::su3heatbath(*m_gaugefield, *m_prng, m_overrelax_steps, fixed_timeslices);
		m_time_spent_sweeping += std::chrono::steady_clock::now() - start_time;
	}

	void set(const double* gauge_field) {
		free_buf();
		m_gaugefield->setToContractionCodeArray(gauge_field);
	}

	void read(std::string filename) {
		auto start_time = std::chrono::steady_clock::now();
		free_buf();
		m_gaugefield->readFromILDGSourcefile(filename);
		m_time_spent_reading += std::chrono::steady_clock::now() - start_time;
	}

	void write(std::string filename) const {
		auto start_time = std::chrono::steady_clock::now();
		m_gaugefield->save(filename, 0);
		m_time_spent_writing += std::chrono::steady_clock::now() - start_time;
	}

	const int get_T() const {
		return m_gaugefield->getParameters()->getNt();
	}

	const int get_L() const {
		return m_gaugefield->getParameters()->getNs();
	}

	const int get_beta() const {
		return m_gaugefield->getParameters()->getBeta();
	}

	const double* get_buffer() {
		auto start_time = std::chrono::steady_clock::now();
		if (m_contractioncode_gaugefield_buf == nullptr) {
			Gauge_Field_Alloc(m_contractioncode_gaugefield_buf, get_T(), get_L());
			m_gaugefield->copyToContractionCodeArray(m_contractioncode_gaugefield_buf);
		}
		m_time_spent_converting += std::chrono::steady_clock::now() - start_time;
		return m_contractioncode_gaugefield_buf;
	}

private:
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

	std::chrono::steady_clock::duration m_time_spent_sweeping { 0 }, m_time_spent_reading { 0 }, m_time_spent_converting { 0 };
	mutable std::chrono::steady_clock::duration m_time_spent_writing { 0 };

};

CL2QCDGaugefield::CL2QCDGaugefield(int T, int L, int seed, double beta, int overrelax_steps, std::string filename) :
		impl { tools::helper::make_unique<Implementation>(T, L, seed, beta, overrelax_steps, filename) } {
}

CL2QCDGaugefield::~CL2QCDGaugefield() = default;

void CL2QCDGaugefield::do_sweep(const std::set<int>& fixed_timeslices) {
	impl->do_sweep(fixed_timeslices);
}

void CL2QCDGaugefield::set(const double* gauge_field) {
	impl->set(gauge_field);
}

void CL2QCDGaugefield::read(const std::string& config_filename) {
	impl->read(config_filename);
}

void CL2QCDGaugefield::write(const std::string& config_filename) const {
	impl->write(config_filename);
}

int CL2QCDGaugefield::get_T() const {
	return impl->get_T();
}
int CL2QCDGaugefield::get_L() const {
	return impl->get_L();
}
double CL2QCDGaugefield::get_beta() const {
	return impl->get_beta();
}

const double* CL2QCDGaugefield::get() const {
	return impl->get_buffer();
}

}
}
}
