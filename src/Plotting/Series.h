#pragma once

#include <string>
#include <vector>

#include "PlotAPI.h"
#include "Appearance.h"

namespace VSCL::Plot {

struct SeriesInfo {
	std::string Name = "";
	std::vector<double> Times = { 0.0 };
	std::vector<double> Quantities = { 0.0 };

	ColorRGB Color = {1.0, 0.0, 0.0};
	double Alpha = 1.0;
	LineStyle Style = LineStyle::Solid;
};

} // namespace VSCL::Plot
