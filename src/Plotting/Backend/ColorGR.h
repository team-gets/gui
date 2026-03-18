#pragma once

#include <map>
#include <cmath>
#include <cstdint>

#include "Plotting/Appearance.h"

namespace VSCL::Plot {

// Reference gr.h 104-123
// The polyline coloring function takes an int < 1024
enum class PLOT_API ColorGR : uint16_t {
	White =		0,
	Black =		1,
	Red =		236,
	Green = 	237,
	Yellow =	238,
	Blue =		239,
	Orange =	240,
	Purple =	241,
	Cyan =		242,
	Magenta =	243,
	Lime =		244,
	Pink =		245,
	Teal =		246,
	Lavender =	247,
	Brown =		248,
	Beige =		249,
	Maroon =	250,
	Mint =		251,
	Olive =		252,
	Apricot =	253,
	Navy =		254,
	Grey =		255
}; // enum class ColorGR

// Reference gks/util.c 213-463
static const PLOT_API std::map<ColorGR, ColorRGB> ColorGRAsRGB = {
	{ ColorGR::White, ColorRGB{1.000000, 1.000000, 1.000000} },
	{ ColorGR::Black, ColorRGB{0.0, 0.0, 0.0} },
	{ ColorGR::Red, ColorRGB{0.901960, 0.098040, 0.294120} },
	{ ColorGR::Green, ColorRGB{0.235290, 0.705880, 0.294120} },
	{ ColorGR::Yellow, ColorRGB{1.000000, 0.882350, 0.098040} },
	{ ColorGR::Blue, ColorRGB{0.000000, 0.509800, 0.784310} },
	{ ColorGR::Orange, ColorRGB{0.960780, 0.509800, 0.188240} },
	{ ColorGR::Purple, ColorRGB{0.568630, 0.117650, 0.705880} },
	{ ColorGR::Cyan, ColorRGB{0.274510, 0.941180, 0.941180} },
	{ ColorGR::Magenta, ColorRGB{0.941180, 0.196080, 0.901960} },
	{ ColorGR::Lime, ColorRGB{0.823530, 0.960780, 0.235290} },
	{ ColorGR::Pink, ColorRGB{0.980390, 0.745100, 0.831370} },
	{ ColorGR::Teal, ColorRGB{0.000000, 0.501960, 0.501960} },
	{ ColorGR::Lavender, ColorRGB{0.862750, 0.745100, 1.000000} },
	{ ColorGR::Brown, ColorRGB{0.666670, 0.431370, 0.156860} },
	{ ColorGR::Beige, ColorRGB{1.000000, 0.980390, 0.784310} },
	{ ColorGR::Maroon, ColorRGB{0.501960, 0.000000, 0.000000} },
	{ ColorGR::Mint, ColorRGB{0.666670, 1.000000, 0.764710} },
	{ ColorGR::Olive, ColorRGB{0.501960, 0.501960, 0.000000} },
	{ ColorGR::Apricot, ColorRGB{1.000000, 0.843140, 0.705880} },
	{ ColorGR::Navy, ColorRGB{0.000000, 0.000000, 0.501960} },
	{ ColorGR::Grey, ColorRGB{0.501960, 0.501960, 0.501960} }
}; // ColorGRAsRGB

/*
 *	Find the RGB-spaced color from the input GR color name.
 */
static const ColorRGB RGBFromColorGR(ColorGR color) {
	return ColorGRAsRGB.at(color);
};

/*
 *	Find a color that's close enough to or matching the input color.
 *
 *	Defaults to RED: ColorRGB{0.901960, 0.098040, 0.294120}
 *
 */
static const ColorGR ColorGRFromRGB(ColorRGB color, double tol = 1e-1) {

	for (std::pair<ColorGR, ColorRGB> colorpair : ColorGRAsRGB) {
		const ColorRGB& rgb = colorpair.second;

		if (std::abs(rgb[0] - color[0]) > tol) { continue; }
		if (std::abs(rgb[1] - color[1]) > tol) { continue; }
		if (std::abs(rgb[2] - color[2]) > tol) { continue; }

		return colorpair.first;
	}

	// default
	return ColorGR::Red;
};

} // VSCL::Plot
