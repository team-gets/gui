#pragma once

#include <cstdint>
#include <array>
#include <string>
#include "PlotAPI.h"

namespace VSCL::Plot {

enum class PLOT_API Axis : std::uint8_t {
	Time = 0,
	Quantity = 1,
};

enum class PLOT_API AxisScaling : std::uint8_t {
	Linear = 0,
	Log10 = 1,
	Ln = 2,
	Inverted = 3
};

struct PLOT_API AxisInfo {
	Axis InfoOf;
	AxisScaling Scaling = AxisScaling::Linear;

	std::array<double, 2> Range = { 0.0, 1.0 };
	double MajorSpacing = 1;
	double MinorSpacing = 0.2;
	std::string Title = "";
};
} // namespace VSCL::Plot
