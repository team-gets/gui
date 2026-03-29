#pragma once

#include <QWidget>
#include <QLabel>

#include "Dial/Attitude.hpp"
#include "Displays/RateLabel.hpp"

namespace VSCL {

/*
 *	Composite dial combines multiple elements together:
 *	Base dial, title, and rate display
 */
class CompositeDial : public QWidget {

	Q_OBJECT;

public:
	CompositeDial(QWidget* parent);
	CompositeDial(const QString& title, QWidget* parent);

	void SetDialTitle(const QString& title);
	void SetDialAngle(double value);
	void DisplayRateFromArray(const std::vector<double>& ts, const std::vector<double>& qtys);

private:
	QGridLayout* MajorOrganizer;
	QGridLayout* DuoOrganizer;
	QLabel* DialNameLabel;
	QWidget* DialRateDuo;
	AttitudeDial* Dial;
	RateLabel* NumericRateLabel;

}; // class CompositeDial
} // namespace VSCL
