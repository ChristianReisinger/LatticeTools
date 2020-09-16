#include <set>
#include <string>

#include <SUNGaugefield.hh>

#ifndef INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_CONTRACTIONCODEGAUGEFIELD_HH_
#define INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_CONTRACTIONCODEGAUGEFIELD_HH_

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

class ContractionCodeGaugefield: public SUNGaugefield {
public:
	ContractionCodeGaugefield(int T, int L, std::string filename);
	ContractionCodeGaugefield(const ContractionCodeGaugefield&) = delete;
	ContractionCodeGaugefield(ContractionCodeGaugefield&&) = delete;
	ContractionCodeGaugefield& operator=(const ContractionCodeGaugefield&) = delete;
	ContractionCodeGaugefield& operator=(ContractionCodeGaugefield&&) = delete;
	~ContractionCodeGaugefield();

	void do_sweep(const std::set<int>& fixed_timeslices) override;
	void set(const double* gauge_field) override;
	void read(const std::string& config_filename) override;

	void write(const std::string& config_filename) const override;
	int get_T() const override;
	int get_L() const override;
	double get_beta() const override;
	const double* get() const override;

private:
	double* m_gaugefield_buf;
	const int m_T, m_L;

};

}
}
}

#endif
