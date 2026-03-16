#pragma once

#include <QtWidgets>

namespace VSCL {

class QtyRateDisplay;

class QtyRateRow : public QGroupBox {

	Q_OBJECT;
	friend class QtyRateDisplay;

public:
	QtyRateRow(const QString& title, QtyRateDisplay* parent);

	void SetQuantity(double newQuantity);
	void SetRate(double newRate);

	void SetQuantityUnits(const QString& units);
	void SetRateUnits(const QString& units);

private:
	QHBoxLayout* Organizer;

	double Quantity = 0.0;
	double Rate = 0.0;

	QString QuantityUnits = tr("");
	QString RateUnits = tr("/s");

	QLabel* QuantityLabel;
	QLabel* RateLabel;

}; // class QtyRateDisplay
} // namespace VSCL
