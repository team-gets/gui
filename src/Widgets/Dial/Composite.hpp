#pragma once

#include <QWidget>
#include <QLabel>

#include "Dial/Attitude.hpp"
#include "Displays/RateLabel.hpp"
#include "Util/Sizing.hpp"

namespace VSCL {

/*
 *	@brief The composite dial combines multiple elements together:
 *	A base dial, title, and rate display.
 */
class CompositeDial : public QWidget {

	Q_OBJECT;

public:
	CompositeDial(QWidget* parent);
	CompositeDial(const QString& title, QWidget* parent);
	virtual void resizeEvent(QResizeEvent* event) override;

	void SetDialTitle(const QString& title);
	void SetDialAngle(double value);
	void DisplayRateFromArray(const std::vector<double>& ts, const std::vector<double>& qtys);

private:
	QGridLayout* MajorOrganizer;
	QLabel* DialNameLabel;
	Util::FontAdjustment TitleAdjustment{ .PointSizeAtMinimum = 20, .AdjustToWidth = false };

	QGridLayout* DuoOrganizer;
	QWidget* DialRateDuo;
	AttitudeDial* Dial;
	RateLabel* NumericRateLabel;

	double RateLimitHz = 1.0;

}; // class CompositeDial
} // namespace VSCL
