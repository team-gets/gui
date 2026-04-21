#pragma once

#include <QWidget>
#include <cstdint>
#include <cmath>

namespace VSCL::Util {

static constexpr uint32_t MINIMUM_WIDTH = 720;
static constexpr uint32_t MINIMUM_HEIGHT = 480;

struct FontAdjustment {
	/*
	 *	The point size at the window's minimum resolution.
	 */
	unsigned int PxSizeAtMinimum = 12;

	/*
	 *	When true, adjust to the width of the window.
	 *	When false, adjust to the height of the window.
	 */
	bool AdjustToWidth = false;

	static const uint32_t AdjustPxSize(uint32_t px_at_min, QWidget* win, bool adjust_to_width=false) {
		uint32_t dim = adjust_to_width ? win->width() : win->height();
		uint32_t adj = adjust_to_width ? MINIMUM_WIDTH : MINIMUM_HEIGHT;
		float delta = (float)(dim - adj) / (float)adj;

		return px_at_min * (uint32_t)std::ceil(1 + delta);
	}

	const uint32_t AdjustPxSize(QWidget* win) const {
		return AdjustPxSize(PxSizeAtMinimum, win, AdjustToWidth);
	}
};
} // namespace VSCL::Util
