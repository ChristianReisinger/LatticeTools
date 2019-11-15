#include <set>

#include <SUNGaugefield.hh>

#ifndef INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_MCSU2GAUGEFIELD_HH_
#define INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_MCSU2GAUGEFIELD_HH_

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

class MCSU2Gaugefield: public SUNGaugefield {
public:
	MCSU2Gaugefield(int T, int L, int seed, double beta);
	MCSU2Gaugefield(const MCSU2Gaugefield&) = delete;
	MCSU2Gaugefield(MCSU2Gaugefield&&) = delete;
	MCSU2Gaugefield& operator=(const MCSU2Gaugefield&) = delete;
	MCSU2Gaugefield& operator=(MCSU2Gaugefield&&) = delete;
	~MCSU2Gaugefield();

	void do_sweep(const std::set<int>& fixed_timeslices = std::set<int>()) const override;

	void write(const std::string& config_filename, const std::string& header) const override;

	void read(const std::string& config_filename) const override;

	int get_T() const override;
	int get_L() const override;
	double get_beta() const override;
	const double* get_buffer() const override;

private:
	double* m_gaugefield_buf;
	const int m_T, m_L;
	const double m_beta;
};

}
}
}

#endif
