#include <QBoxLayout>
#include <QPainter>

#include <algorithm>
#include <cmath>

#include "AttitudeDial.hpp"

namespace VSCL {

AttitudeDial::AttitudeDial(QWidget* parent) : QWidget(parent) {
	SetRangeType(RangeTypeMode);
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

QPoint AttitudeDial::HandEndingLowestNominal() const {
	double ang = (CurrentAngle - Range[0]) * 3.14 / 180.0;
	int linex = Radius*std::sin(ang);
	int liney = -Radius*std::cos(ang);

	return Origin + QPoint{ linex, liney };
}

QPoint AttitudeDial::HandEndingCenteredNominal() const {
	double rangeCtr = (Range[1] - Range[0]) / 2.0;
	double ang = (CurrentAngle - rangeCtr) * 3.14 / 180.0;
	int linex = -Radius*std::sin(ang);
	int liney = Radius*std::cos(ang);

	return Origin + QPoint{ linex, liney };
}

void AttitudeDial::SetRangeType(RangeType newRangeType) {
	RangeTypeMode = newRangeType;
	
	switch (RangeTypeMode) {
	case RangeType::LowestNominal:
		RangeHandlerFunction = std::bind(&AttitudeDial::HandEndingLowestNominal, this);
		break;
	case RangeType::CenteredNominal:
	default:
		RangeHandlerFunction = std::bind(&AttitudeDial::HandEndingCenteredNominal, this);
		break;
	}

	update();
}

void AttitudeDial::PaintCircularBacking(QPainter* painter) {
	QBrush fillBrush = painter->brush();
	fillBrush.setStyle(Qt::SolidPattern);
	fillBrush.setColor(Palette.Primary);

	painter->setBrush(fillBrush);
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->drawEllipse(Origin, (int)Radius, (int)Radius);
} // void AttitudeDial::PaintCircularBacking()

void AttitudeDial::PaintTicks(QPainter* painter) {
	for (int i = 0; i < 8; i++) {
		QColor tickcolor;
		std::array<double, 2> ticker = { 0.0, 1.0 };
		std::array<double, 2> cossin;

		switch (i) {
		case 0:
		case 1:
		case 2:
		case 3: // major
			ticker[0] = 0.85;
			tickcolor = Palette.MajorTick;
			cossin = MajorTicks[i];
			break;
		default: // minor
			ticker[0] = 0.95;
			tickcolor = Palette.MinorTick;
			cossin = MinorTicks[i - 4];
			break;
		}

		qDebug() << cossin;
		double ci = Radius * cossin[0];
		double si = Radius * cossin[1];
		QPen pen = painter->pen();
		pen.setColor(tickcolor);

		QPoint st = Origin + ticker[0] * QPoint{ int(ci), int(si) };
		QPoint ed = Origin + ticker[1] * QPoint{ int(ci), int(si) };
		painter->setPen(pen);
		painter->drawLine(st, ed);
	}
} // void AttitudeDial::PaintTicks()

void AttitudeDial::PaintHand(QPainter* painter) {
	QPoint end = (RangeHandlerFunction) ? RangeHandlerFunction(this) : Origin + QPoint{ 0, (int)Radius };

	QPen pen = painter->pen();
	pen.setColor(Palette.Hand);

	painter->setPen(pen);
	painter->drawLine(Origin, end);
} // AttitudeDial::PaintHand()

void AttitudeDial::PaintCap(QPainter* painter) {
	QBrush fillBrush = painter->brush();
	fillBrush.setStyle(Qt::SolidPattern);
	fillBrush.setColor(Palette.Cap);

	int r = (int)(0.02*Radius);
	painter->setBrush(fillBrush);
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->drawEllipse(Origin, r, r);
} // AttitudeDial::PaintCap()

void AttitudeDial::SetPalette(AttitudeDialPalette& newPalette) { Palette = newPalette; }
AttitudeDialPalette AttitudeDial::GetPalette() const { return Palette; }
const AttitudeDialPalette& AttitudeDial::GetPaletteView() const { return Palette; }

void AttitudeDial::paintEvent(QPaintEvent* event) { 
	UpdateRadius();
	UpdateOrigin();

	QPainter painter(this);
	PaintCircularBacking(&painter);
	PaintTicks(&painter);
	PaintHand(&painter);
	PaintCap(&painter);
}
} // namespace VSCL
