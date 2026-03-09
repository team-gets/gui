#include <QBoxLayout>
#include <QPainter>

#include <algorithm>
#include <cmath>

#include "AttitudeDial.h"

namespace VSCL {

AttitudeDial::AttitudeDial(QWidget* parent) : QWidget(parent) {
	setParent(parent);
	setMinimumSize(128, 128);

	QVBoxLayout* box = new QVBoxLayout;
	setLayout(box);

	update();
} // AttitudeDial ctor

void AttitudeDial::SetDialAngle(double value) {
	CurrentAngle = value;
	update();
}

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
} // void AttitudeDial::PaintCircularBacking()

void AttitudeDial::PaintHand(QPaintEvent* event, QPainter* painter) {
	QSize curSize = size();
	QPoint origin = { curSize.width() / 2, curSize.height() / 2 };

	double rx = curSize.width() / 2.0 * 0.95;
	double ry = curSize.height() / 2.0 * 0.95;
	double r = std::min<double>(rx, ry);

	double ang = CurrentAngle * 3.14 / 180.0;
	int linex = r*std::sin(ang);
	int liney = -r*std::cos(ang);
	QPoint end = origin + QPoint{ linex, liney };

	QPen pen = painter->pen();
	pen.setColor(QColorConstants::DarkGray);

	painter->setPen(pen);
	painter->drawLine(origin, end);
} // AttitudeDial::PaintHand()

void AttitudeDial::paintEvent(QPaintEvent* event) { 
	QPainter painter(this);
	PaintCircularBacking(event, &painter);
	PaintHand(event, &painter);
}
} // namespace VSCL
