#include <set>
#include <string>

#ifndef INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_SUNINTERFACE_HH_
#define INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_SUNINTERFACE_HH_

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

class SUNInterface {
public:
	virtual ~SUNInterface() = default;

	virtual void do_sweep(double* const config_buf, int T, int L, double beta,
			const std::set<int>& fixed_timeslices = std::set<int>()) const = 0;

	virtual void write_gauge_field(const double* const config_buf, const std::string& config_filename, int T, int L,
			const std::string& header) const = 0;

	virtual void read_gauge_field(double* const config_buf, const std::string& config_filename, int T, int L) const = 0;

};

}
}
}
