#pragma once

#include <QtWidgets>

namespace VSCL {

class QtyRateDisplay;

class QtyRateRow : public QFrame {

	Q_OBJECT;
	friend class QtyRateDisplay;

public:
	QtyRateRow(QtyRateDisplay* parent);

	void SetQuantity(double newQuantity);
	void SetRate(double newRate);

private:
	double Quantity;
	double Rate;
	QLabel* QuantityLabel;
	QLabel* QuantityRateLabel;

}; // class QtyRateDisplay
} // namespace VSCL
