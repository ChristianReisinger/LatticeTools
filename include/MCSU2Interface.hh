#include <set>

#include <SUNInterface.hh>

#ifndef INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_MCSU2INTERFACE_HH_
#define INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_MCSU2INTERFACE_HH_

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

class MCSU2Interface: public SUNInterface {
public:
	void do_sweep(double* config_buf, int T, int L, double beta,
			const std::set<int>& fixed_timeslices = std::set<int>()) const override;

	void write_gauge_field(const double* config_buf, const std::string& config_filename, int T, int L,
				const std::string& header) const override;

	void read_gauge_field(double* config_buf, const std::string& config_filename, int T, int L) const override;
};

}
}
}
