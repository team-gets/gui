#pragma once

#include <QtWidgets>
#include "Util/Sizing.hpp"

namespace VSCL {

class QtyRateDisplay;

class QtyRateRow : public QGroupBox {

	Q_OBJECT;
	friend class QtyRateDisplay;

public:
	QtyRateRow(const QString& title, QtyRateDisplay* parent);
	virtual void resizeEvent(QResizeEvent* event);

	void SetQuantity(double new_quantity);
	void SetRate(double new_rate);

	void SetQuantityUnits(const QString& units);
	void SetRateUnits(const QString& units);

private:

	double Quantity = 0.0;
	double Rate = 0.0;

	QString QuantityUnits = tr("");
	QString RateUnits = tr("/s");

	QString Title;
	QFont TitleFont{ };
	QFont LabelFont{ };

	QHBoxLayout* Organizer;
	QLabel* QuantityLabel;
	QLabel* RateLabel;

	void AdjustFontSize();
	static constexpr Util::FontAdjustment TITLE_FONT_ADJUSTMENT { 8, false };
	static constexpr Util::FontAdjustment NUMERIC_FONT_ADJUSTMENT { 8, false };

}; // class QtyRateDisplay
} // namespace VSCL
