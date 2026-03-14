#include <QBoxLayout>
#include <QPainter>

#include <algorithm>
#include <cmath>

#include "AttitudeDial.h"

namespace VSCL {

AttitudeDial::AttitudeDial(QWidget* parent) : QWidget(parent) {
	update();
} // AttitudeDial ctor

void AttitudeDial::SetDialAngle(double value) {
	CurrentAngle = value;
	update();
}

void AttitudeDial::UpdateRadius() {
	QSize curSize = size();

	double rx = curSize.width() / 2.0 * 0.95;
	double ry = curSize.height() / 2.0 * 0.95;

	Radius = std::min<double>(rx, ry);
}

void AttitudeDial::UpdateOrigin() {
	QSize curSize = size();
	Origin = { curSize.width() / 2, curSize.height() / 2 };
}

void AttitudeDial::PaintCircularBacking(QPaintEvent* event, QPainter* painter) {
	QBrush fillBrush = painter->brush();
	fillBrush.setStyle(Qt::SolidPattern);
	fillBrush.setColor(QColorConstants::White);

	painter->setBrush(fillBrush);
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->drawEllipse(Origin, (int)Radius, (int)Radius);
} // void AttitudeDial::PaintCircularBacking()

void AttitudeDial::PaintTicks(QPaintEvent* event, QPainter* painter) {

} // void AttitudeDial::PaintTicks()

void AttitudeDial::PaintHand(QPaintEvent* event, QPainter* painter) {
	double ang = CurrentAngle * 3.14 / 180.0;
	int linex = Radius*std::sin(ang);
	int liney = -Radius*std::cos(ang);
	QPoint end = Origin + QPoint{ linex, liney };

	QPen pen = painter->pen();
	pen.setColor(QColorConstants::DarkGray);

	painter->setPen(pen);
	painter->drawLine(Origin, end);
} // AttitudeDial::PaintHand()

void AttitudeDial::paintEvent(QPaintEvent* event) { 
	UpdateRadius();
	UpdateOrigin();

	QPainter painter(this);
	PaintCircularBacking(event, &painter);
	PaintHand(event, &painter);
}
} // namespace VSCL
