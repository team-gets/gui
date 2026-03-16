#pragma once

#include <QWidget>

namespace VSCL::Util {

constexpr int MinimumWidth = 480;
constexpr int MinimumHeight = 720;

struct FontAdjustment {
	int PointSizeAtMinimum;
	bool AdjustToWidth = true;
	const int AdjustPointSize(QWidget* parent) const {
		return PointSizeAtMinimum
			+ ((AdjustToWidth) ?
					(parent->width() - MinimumWidth) / MinimumWidth
					: (parent->height() - MinimumHeight) / MinimumHeight);
	}
};
} // namespace VSCL::Util
