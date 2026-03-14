#pragma once

#include <cstdint>
#include <array>
#include <string>
#include <map>

namespace VSCL::Plot {

// Normalized in RGB space.
typedef std::array<double, 3> ColorRGB;

static const std::map<std::string, ColorRGB> StandardColor = {
	{ "Red",	ColorRGB{ 1.0, 0.0, 0.0 } },
	{ "Green",	ColorRGB{ 0.0, 1.0, 0.0 } },
	{ "Blue",	ColorRGB{ 0.0, 0.0, 1.0 } },
};

enum class LineStyle : uint8_t {
	Solid = 1,
	Dashed = 2,
};
} // namespace VSCL::Plot
