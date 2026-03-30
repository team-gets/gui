#pragma once

#include <array>

namespace VSCL::Util {

static constexpr double CenterFiniteDifference(const std::array<double, 3>& ts, const std::array<double, 3>& qtys) {
	double h = (ts[2] - ts[0]) / 2.0;
	double fwd = (qtys[2] - qtys[1]) / 2.0;
	double bkd = (qtys[1] - qtys[0]) / 2.0;
	
	return (fwd - bkd) / h;
}
} // namespace VSCL::Util
