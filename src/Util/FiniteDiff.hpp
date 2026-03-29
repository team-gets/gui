#pragma once

#include <array>
#include <type_traits>

namespace VSCL::Util {

template<typename T>
static constexpr T CenterFiniteDifference(std::array<T, 3> ts, std::array<T, 3> vals) {
	static_assert(std::is_floating_point<T>());

	constexpr double h = (ts[2] - ts[0]) / 2.0;
	constexpr double fwd = (vals[2] - vals[1]) / 2.0;
	constexpr double bkd = (vals[1] - vals[0]) / 2.0;
	
	return (fwd - bkd) / h;
}
} // namespace VSCL::Util
