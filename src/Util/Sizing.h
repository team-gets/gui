#pragma once

#include <QWidget>

namespace VSCL::Util {

constexpr int MinimumWidth = 720;
constexpr int MinimumHeight = 480;

struct FontAdjustment {
	int PointSizeAtMinimum;
	bool AdjustToWidth = false;
	const int AdjustPointSize(QWidget* win) const {
		qDebug() << win->size();
		return PointSizeAtMinimum
			+ ((AdjustToWidth) ?
					(win->width() - MinimumWidth) / MinimumWidth
					: (win->height() - MinimumHeight) / MinimumHeight);
	}
};
} // namespace VSCL::Util
