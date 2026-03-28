#pragma once

#include <array>
#include <QtWidgets>

namespace VSCL {
struct AttitudeDialPalette {
	QColor Primary = QColorConstants::White;
	QColor Hand = QColorConstants::Black;
	QColor Cap = QColorConstants::Black;
	QColor MajorTick = QColorConstants::DarkGray;
	QColor MinorTick = QColorConstants::DarkGray;
};

class AttitudeDial : public QWidget {

	Q_OBJECT;

public:
	AttitudeDial(QWidget* parent);
	AttitudeDial(QWidget* parent, bool enabled);

	void SetDialAngle(double value);
	void SetNumericDisplayState(bool enabled);

	void SetPalette(AttitudeDialPalette& newPalette);
	AttitudeDialPalette GetPalette() const;
	const AttitudeDialPalette& GetPaletteView() const;

	virtual void paintEvent(QPaintEvent* event) override;

private:
	double CurrentAngle = 0.0;
	QPoint Origin = { 0, 0 };
	double Radius = 1.0;
	void UpdateOrigin();
	void UpdateRadius();

	AttitudeDialPalette Palette;

	QFont NumericDisplayFont;
	QLabel* NumericDisplay;
	bool NumericDisplayEnabled = true;
	void UpdateNumericFont();
	void UpdateNumericDisplay();

	void PaintCircularBacking(QPainter* painter);
	void PaintTicks(QPainter* painter);
	void PaintHand(QPainter* painter);
	void PaintCap(QPainter* painter);

	static constexpr std::array<double, 12> Cos30Degs = {
		1.0, 0.8660254037844387, 0.5, 0.0,
		-0.5, -0.8660254037844387, -1.0, -0.8660254037844387, 
		-0.5, 0.0, 0.5, 0.8660254037844387 
	};
	static constexpr std::array<double, 12> Sin30Degs = {
		0.0, 0.5, 0.8660254037844387, 1.0,
		0.8660254037844387, 0.5, 0.0, -0.5,
		-0.8660254037844387, -1.0, -0.8660254037844387, -0.5
	};

}; // class AttitudeDial
} // namespace VSCL
