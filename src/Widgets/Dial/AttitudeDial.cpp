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

void AttitudeDial::PaintCircularBacking(QPaintEvent* event, QPainter* painter) {
	QSize curSize = size();
	QPoint origin = { curSize.width() / 2, curSize.height() / 2 };

	double rx = curSize.width() / 2.0 * 0.95;
	double ry = curSize.height() / 2.0 * 0.95;
	double r = std::min<double>(rx, ry);

	QBrush fillBrush = painter->brush();
	fillBrush.setStyle(Qt::SolidPattern);
	fillBrush.setColor(QColorConstants::White);

	painter->setBrush(fillBrush);
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->drawEllipse(origin, (int)r, (int)r);
} // void PaintCircularBacking

void AttitudeDial::paintEvent(QPaintEvent* event) { 
	QPainter painter(this);
	PaintCircularBacking(event, &painter);
}
} // namespace VSCL
