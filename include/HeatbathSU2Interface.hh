#include <set>

#include <HeatbathInterface.hh>

#ifndef INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_HEATBATHSU2INTERFACE_HH_
#define INCLUDE_DE_UNI_FRANKFURT_ITP_REISINGER_LATTICETOOLS_0719_HEATBATHSU2INTERFACE_HH_

namespace de_uni_frankfurt_itp {
namespace reisinger {
namespace latticetools_0719 {

class HeatbathSU2Interface : public HeatbathInterface {
public:
	void do_sweep(double* const config_buf, int T, int L, double beta,
			const std::set<int>& fixed_timeslices = std::set<int>()) const override;
};

}
}
}
