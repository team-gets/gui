#pragma once

#include <QtWidgets>
#include "Util/Sizing.h"

namespace VSCL {

class QtyRateDisplay;

class QtyRateRow : public QGroupBox {

	Q_OBJECT;
	friend class QtyRateDisplay;

public:
	QtyRateRow(const QString& title, QtyRateDisplay* parent);
	virtual void resizeEvent(QResizeEvent* event);

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

	QString Title;
	QFont TitleFont;
	QFont LabelFont;
	QLabel* QuantityLabel;
	QLabel* RateLabel;

	void AdjustFontSize();
	static constexpr Util::FontAdjustment TitleFontAdjustment { 8, false };
	static constexpr Util::FontAdjustment NumericFontAdjustment { 8, false };

}; // class QtyRateDisplay
} // namespace VSCL
