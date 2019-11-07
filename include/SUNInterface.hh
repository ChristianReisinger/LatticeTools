#include <set>
#include <string>
#include <algorithm>

#include <global_defs.hh>

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

	virtual void write_gauge_field(const double* config_buf, const std::string& config_filename, int T, int L,
			const std::string& header) const = 0;

	virtual void read_gauge_field(double* config_buf, const std::string& config_filename, int T, int L) const = 0;

	inline void Gauge_Field_Alloc(double*& gauge_field, int T, int L) const {
		gauge_field = new double[T * L * L * L * 4 * SUN_elems];
	}

	inline void Gauge_Field_Free(double*& gauge_field) const {
		delete[] gauge_field;
	}

	inline void Gauge_Field_Copy(const double*& dest, const double* src, int T, int L) const {
		std::copy(src, src + T * L * L * L * 4 * SUN_elems, dest);
	}
};

}
}
}
