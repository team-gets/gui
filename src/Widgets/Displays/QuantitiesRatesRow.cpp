#include "QuantitiesRatesRow.hpp"
#include "QuantitiesRatesDisplay.hpp"

namespace VSCL {
QtyRateRow::QtyRateRow(const QString& title, QtyRateDisplay* parent)
	: QGroupBox(title, parent)
	, Title(title)
	, Organizer(new QHBoxLayout(this))
	, QuantityLabel(new QLabel(this))
	, RateLabel(new QLabel(this)) {

	parent->AddRow(this);
	setLayout(Organizer);

	Organizer->setContentsMargins(5, 5, 5, 5);
	Organizer->addWidget(QuantityLabel);
	Organizer->addWidget(RateLabel);

	QuantityLabel->setText(QString::number(Quantity) + QuantityUnits);
	RateLabel->setText(QString::number(Rate) + RateUnits);

	AdjustFontSize();
}

void QtyRateRow::resizeEvent(QResizeEvent* event) {
	QGroupBox::resizeEvent(event);
	AdjustFontSize();
}

void QtyRateRow::AdjustFontSize() {
	uint32_t tpt = static_cast<uint32_t>(TitleFontAdjustment.AdjustPxSize(window()));
	if (tpt <= TitleFontAdjustment.PxSizeAtMinimum) {
		setTitle(tr(""));
		TitleFont.setPixelSize(1);
	}
	else {
		setTitle(Title);
		TitleFont.setPixelSize(tpt);
	}

	setFont(TitleFont);

	LabelFont.setPixelSize(NumericFontAdjustment.AdjustPxSize(window()));
	QuantityLabel->setFont(LabelFont);
	RateLabel->setFont(LabelFont);
}

void QtyRateRow::SetQuantity(double newQuantity) {
	Quantity = newQuantity;
	QuantityLabel->setText(QString::number(Quantity) + QuantityUnits);
}
void QtyRateRow::SetRate(double newRate) {
	Rate = newRate;
	RateLabel->setText(QString::number(Rate) + RateUnits);
}

void QtyRateRow::SetQuantityUnits(const QString& units) { QuantityUnits = units; }
void QtyRateRow::SetRateUnits(const QString& units) { RateUnits = units; }

} // namespace VSCL

