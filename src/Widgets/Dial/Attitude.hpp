#pragma once

#include <cstdint>
#include <array>
#include <QtWidgets>

namespace VSCL {
struct AttitudeDialPalette {
	QColor Primary = QColorConstants::White;
	QColor Hand = QColorConstants::Red;
	QColor Cap = QColorConstants::Black;
	QColor MajorTick = QColorConstants::DarkGray;
	QColor MinorTick = QColorConstants::LightGray;
};

class AttitudeDial : public QWidget {

	Q_OBJECT;

public:
	AttitudeDial(QWidget* parent);

	void SetDialAngle(double value);
	void SetPalette(AttitudeDialPalette& newPalette);
	AttitudeDialPalette GetPalette() const;
	const AttitudeDialPalette& GetPaletteView() const;

	enum class RangeType : uint8_t {
		CenteredNominal,
		LowestNominal
	};
	void SetRangeType(RangeType newRangeType);

	virtual void paintEvent(QPaintEvent* event) override;

private:
	double CurrentAngle = 0.0;
	QPoint Origin = { 0, 0 };
	double Radius = 1.0;
	void UpdateOrigin();
	void UpdateRadius();

	AttitudeDialPalette Palette;
	std::array<double, 2> Range = { -180, 180 };
	RangeType RangeTypeMode = RangeType::CenteredNominal;
	QPoint HandEndingLowestNominal() const;
	QPoint HandEndingCenteredNominal() const;
	std::function<QPoint(const AttitudeDial&)> RangeHandlerFunction = nullptr;

	void PaintCircularBacking(QPainter* painter);
	void PaintTicks(QPainter* painter);
	void PaintHand(QPainter* painter);
	void PaintCap(QPainter* painter);

	static constexpr std::array<std::array<double, 2>, 4> MajorTicks = {{
		{ 1.0, 0.0 }, { 0.0, 1.0 }, { -1.0, 0.0 }, { 0.0, -1.0 }
	}};

	static constexpr std::array<std::array<double, 2>, 4> MinorTicks = {{
		{ 0.7071067811865475, 0.7071067811865475 }, { 0.7071067811865475, -0.7071067811865475 },
		{ -0.7071067811865475, -0.7071067811865475 }, { -0.7071067811865475, 0.7071067811865475 } 
	}};
}; // class AttitudeDial
} // namespace VSCL
