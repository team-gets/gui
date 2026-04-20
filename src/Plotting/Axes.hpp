#pragma once

#include <cstdint>
#include <array>
#include <string>

namespace VSCL::Plot {

enum class AXIS : std::uint8_t {
	TIME = 0,
	QUANTITY = 1,
};

enum class AXIS_SCALING : std::uint8_t {
	LINEAR = 0,
	LOG10 = 1,
	LN = 2,
	INVERTED = 3
};

struct AxisInfo {
	AXIS InfoOf;
	AXIS_SCALING Scaling = AXIS_SCALING::LINEAR;

	std::array<double, 2> Range = { 0.0, 1.0 };
	double MajorSpacing = 1;
	double MinorSpacing = 0.2;
	std::string Title = "";
};
} // namespace VSCL::Plot
