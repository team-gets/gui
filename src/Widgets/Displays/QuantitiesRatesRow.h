#pragma once

#include <QtWidgets>

namespace VSCL {

class QuantitiesRatesDisplay;

class QuantitiesRatesRow : public QFrame {

	Q_OBJECT;
	friend class QuantitiesRatesDisplay;

public:
	QuantitiesRatesRow(QuantitiesRatesDisplay* parent);

	void SetQuantity(double newQuantity);
	void SetRate(double newRate);

private:
	double Quantity;
	double Rate;
	QLabel* QuantityLabel;
	QLabel* QuantityRateLabel;

}; // class QuantitiesRatesDisplay
} // namespace VSCL
