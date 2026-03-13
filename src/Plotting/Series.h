#pragma once

#include <vector>

#include "Appearance.h"

namespace VSCL::Plot {

struct SeriesInfo {
	std::vector<double> Times;
	std::vector<double> Quantities;

	ColorRGB Color = {1.0, 0.0, 0.0};
	double Alpha = 1.0;
};

} // namespace VSCL::Plot
