#pragma once

#include <array>
#include <QtWidgets>

namespace VSCL {
class AttitudeDial : public QWidget {

	Q_OBJECT;

public:
	AttitudeDial(QWidget* parent);
	void SetDialAngle(double value);
	virtual void paintEvent(QPaintEvent* event) override;

private:
	double CurrentAngle = 0.0;
	double Radius = 1.0;
	

	void PaintCircularBacking(QPaintEvent* event, QPainter* painter);
	void PaintTicks(QPaintEvent* event, QPainter* painter);
	void PaintHand(QPaintEvent* event, QPainter* painter);

	static constexpr std::array<double, 12> Cos15Degs = {
		1.0, 0.8660254037844387, 0.5, 0.0,
		-0.5, -0.8660254037844387, -1.0, -0.8660254037844387, 
		-0.5, 0.0, 0.5, 0.8660254037844387 
	};
	static constexpr std::array<double, 12> Sin15Degs = {
		0.0, 0.5, 0.8660254037844387, 1.0,
		0.8660254037844387, 0.5, 0.0, -0.5,
		-0.8660254037844387, -1.0, -0.8660254037844387, -0.5
	};

}; // class AttitudeDial
} // namespace VSCL
