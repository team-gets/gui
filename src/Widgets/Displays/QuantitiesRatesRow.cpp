#include "QuantitiesRatesRow.h"
#include "QuantitiesRatesDisplay.h"

namespace VSCL {
QtyRateRow::QtyRateRow(const QString& title, QtyRateDisplay* parent) : QGroupBox(title, parent) {
	parent->AddRow(this);

	Organizer = new QHBoxLayout;
	Organizer->setContentsMargins(5, 5, 5, 5);
	setLayout(Organizer);

	QuantityLabel = new QLabel(this);
	QuantityLabel->setText(QString::number(Quantity) + QuantityUnits);
	Organizer->addWidget(QuantityLabel);
	RateLabel = new QLabel(this);
	RateLabel->setText(QString::number(Rate) + RateUnits);
	Organizer->addWidget(RateLabel);
}

void QtyRateRow::SetQuantity(double newQuantity) { Quantity = newQuantity; }
void QtyRateRow::SetRate(double newRate) { Rate = newRate; }

void QtyRateRow::SetQuantityUnits(const QString& units) { QuantityUnits = units; }
void QtyRateRow::SetRateUnits(const QString& units) { RateUnits = units; }

} // namespace VSCL

