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
	QFont DialNameFont{ };
	Util::FontAdjustment TitleAdjustment{ 16, false };

	QWidget* DialRateDuo;
	QGridLayout* DuoOrganizer;
	AttitudeDial* Dial;
	RateLabel* NumericRateLabel;

}; // class CompositeDial
} // namespace VSCL
