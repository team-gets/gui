#pragma once

#include <string>
#include <vector>

#include "Appearance.hpp"

namespace VSCL::Plot {

struct SeriesInfo {
	std::string Name = "";
	std::vector<double> Times = {  };
	std::vector<double> Quantities = {  };

	ColorRGB Color = {1.0, 0.0, 0.0};
	double Alpha = 1.0;
	LINE_STYLE Style = LINE_STYLE::SOLID;
};
} // namespace VSCL::Plot
