#pragma once

#include <cstdint>
#include <array>
#include <string>

namespace VSCL::Plot {

enum class Axis : std::uint8_t {
	Time = 0,
	Quantity = 1,
};

enum class AxisScaling : std::uint8_t {
	Linear,
	Logarithmic
};

struct AxisInfo {
	Axis InfoOf;
	AxisScaling Scaling;

	std::array<double, 2> Range;
	double Spacing;
	std::string Title;
};
} // namespace VSCL::Plot
