#pragma once

#include <QtWidgets>

namespace VSCL {
class AttitudeDial : public QWidget {

	Q_OBJECT;

public:
	AttitudeDial(QWidget* parent);
	void SetDialValue(double value);
	virtual void paintEvent(QPaintEvent* event) override;

private:
	double CurrentValue = 0.0;
	void PaintCircularBacking(QPaintEvent* event, QPainter* painter);

}; // class AttitudeDial
} // namespace VSCL
