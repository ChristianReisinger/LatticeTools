#include <set>
#include <string>
#include <algorithm>

#include <global_defs.hh>

#ifndef INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_SUNGAUGEFIELD_HH_
#define INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_SUNGAUGEFIELD_HH_

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

class SUNGaugefield {
public:
	virtual ~SUNGaugefield() = default;

	virtual void do_sweep(const std::set<int>& fixed_timeslices = std::set<int>()) = 0;
	virtual void set(const double* gauge_field) = 0;
	virtual void read(const std::string& config_filename) = 0;

	virtual void write(const std::string& config_filename) const = 0;
	virtual int get_T() const = 0;
	virtual int get_L() const = 0;
	virtual double get_beta() const = 0;
	virtual const double* get() = 0;
};

}
}
}

#endif

