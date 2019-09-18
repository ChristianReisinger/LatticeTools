#include <iostream>
#include <sstream>

#include <fields.hh>
#include <io.hh>
#include <geometry.hh>
#include <linear_algebra.hh>
#include <ranlux.hh>
#include <ranlxd.h>
#include <ranlxs.h>

#include <geometry2.hh>

int main(int argc, char **argv) {
	using namespace de_uni_frankfurt_itp::reisinger::latticetools_0719;
	if (argc < 7) {
		std::cout << "Usage: " << argv[0] << " <T> <L> <gauge_field_1_file> <gauge_field_2_file> <t> <out_file>\n";
		return 0;
	}

	int T, L, t_split;
	std::stringstream TLt_ss;
	TLt_ss << argv[1] << " " << argv[2] << " " << argv[5];
	TLt_ss >> T >> L >> t_split;
	if (TLt_ss.fail()) {
		std::cerr << "Error: could not read <T> and/or <L>\n";
		return 0;
	}

	double* g1;
	double* g2;
	Gauge_Field_Alloc(&g1, T, L);
	Gauge_Field_Alloc(&g2, T, L);
	read_gauge_field(g1, argv[3], T, L);
	read_gauge_field(g2, argv[4], T, L);

	double* g_composite;
	Gauge_Field_Alloc(&g_composite, T, L);
	for (int t = 0; t < T; ++t) {
		for (int x = 0; x < L; ++x) {
			for (int y = 0; y < L; ++y) {
				for (int z = 0; z < L; ++z) {
					for (int i = 0; i < 4; ++i) {
						int index = ggi_n(t, x, y, z, 4, i, T, L);
						if (t < t_split)
							cm_eq_cm(g_composite + index, g1 + index);
						else
							cm_eq_cm(g_composite + index, g2 + index);
					}
				}
			}
		}
	}
	std::ostringstream header_oss;
	header_oss << "composite of " << argv[3] << " " << argv[4] << ", split t = " << t_split;
	write_gauge_field(g_composite, argv[6], T, L, header_oss.str().c_str());
}
