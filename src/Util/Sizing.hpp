#pragma once

#include <QWidget>

namespace VSCL::Util {

static constexpr int MinimumWidth = 720;
static constexpr int MinimumHeight = 480;

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

	const int AdjustPxSize(QWidget* win) const {
		return PxSizeAtMinimum
			+ ((AdjustToWidth) ?
					(win->width() - MinimumWidth) / MinimumWidth
					: (win->height() - MinimumHeight) / MinimumHeight);
	}
};
} // namespace VSCL::Util
