#include <set>
#include <memory>

#include <SUNInterface.hh>

#ifndef INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_CL2QCDINTERFACE_HH_
#define INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_CL2QCDINTERFACE_HH_

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

class CL2QCDInterface: public SUNInterface {
public:
	CL2QCDInterface(int T, int L, int seed, double beta, int overrelax_steps);
	CL2QCDInterface(const CL2QCDInterface&) = delete;
	CL2QCDInterface(CL2QCDInterface&&) = delete;
	CL2QCDInterface& operator=(const CL2QCDInterface&) = delete;
	CL2QCDInterface& operator=(CL2QCDInterface&&) = delete;

	void do_sweep(double* config_buf,
			const std::set<int>& fixed_timeslices = std::set<int>()) const override;

	void write_gauge_field(const double* config_buf, const std::string& config_filename,
				const std::string& header) const override;

	void read_gauge_field(double* config_buf, const std::string& config_filename) const override;

	int get_T() const override;
	int get_L() const override;
	double get_beta() const override;

private:
	class Implementation;
	std:: unique_ptr<Implementation> impl;
};

}
}
}

#endif
