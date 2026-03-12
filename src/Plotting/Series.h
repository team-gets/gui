#pragma once

#include <vector>

#include "Appearance.h"

namespace VSCL::Plot {

struct SeriesInfo {
	std::vector<double> Times;
	std::vector<double> Quantities;

	ColorRGB Color;
	double Alpha;
};

} // namespace VSCL::Plot
