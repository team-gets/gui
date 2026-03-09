#include <QBoxLayout>
#include <QPainter>

#include <algorithm>

#include "AttitudeDial.h"

namespace VSCL {

AttitudeDial::AttitudeDial(QWidget* parent) {
	setParent(parent);
	setMinimumSize(128, 128);

	QVBoxLayout* box = new QVBoxLayout;
	setLayout(box);

	update();
} // AttitudeDial ctor

void AttitudeDial::paintEvent(QPaintEvent* event) { 
	QSize curSize = size();
	QPoint origin = { curSize.width() / 2, curSize.height() / 2 };

	double rx = curSize.width() / 2.0 * 0.95;
	double ry = curSize.height() / 2.0 * 0.95;
	double r = std::min<double>(rx, ry);

	QPainter painter(this);
	QBrush brush = painter.brush();
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(QColorConstants::White);
	painter.setBrush(brush);
	painter.drawEllipse(origin, (int)r, (int)r);
}
} // namespace VSCL
