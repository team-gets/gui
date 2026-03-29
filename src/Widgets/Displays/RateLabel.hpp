#pragma once

#include <QLabel>

namespace VSCL {

/*
 *	A label that automatically computes and displays a finite difference on an attached array.
 */
class RateLabel : public QLabel {

	Q_OBJECT;

public:
	RateLabel(QWidget* parent);

	void SetTextFrom(double num);
	void SetRateFromArray(const std::vector<double>& ts, const std::vector<double>& qtys);
	void DisplayRateFromArray(const std::vector<double>& ts, const std::vector<double>& qtys);

private:
	double Rate = 0.0;
	QString QuantityUnitString = "";
	QString TimeUnitString = "/s";

}; // class RateLabel
} // namespace VSCL
