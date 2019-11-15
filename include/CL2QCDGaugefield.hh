#include <set>
#include <memory>
#include <string>

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

	void write(const std::string& config_filename, const std::string& header) const override;
	int get_T() const override;
	int get_L() const override;
	double get_beta() const override;
	const double* get_buffer() const override;

private:
	class Implementation;
	std:: unique_ptr<Implementation> impl;
};

}
}
}

#endif
