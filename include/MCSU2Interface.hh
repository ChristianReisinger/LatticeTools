#include <set>

#include <SUNInterface.hh>

#ifndef INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_MCSU2INTERFACE_HH_
#define INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_MCSU2INTERFACE_HH_

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

class MCSU2Interface: public SUNInterface {
public:
	MCSU2Interface(int T, int L, int seed, double beta);
	MCSU2Interface(const MCSU2Interface&) = delete;
	MCSU2Interface(MCSU2Interface&&) = delete;
	MCSU2Interface& operator=(const MCSU2Interface&) = delete;
	MCSU2Interface& operator=(MCSU2Interface&&) = delete;

	void do_sweep(double* config_buf,
			const std::set<int>& fixed_timeslices = std::set<int>()) const override;

	void write_gauge_field(const double* config_buf, const std::string& config_filename,
				const std::string& header) const override;

	void read_gauge_field(double* config_buf, const std::string& config_filename) const override;

	int get_T() const override;
	int get_L() const override;
	double get_beta() const override;

private:
	const int m_T, m_L;
	const double m_beta;
};

}
}
}

#endif
