#include "QuantitiesRatesRow.hpp"
#include "QuantitiesRatesDisplay.hpp"

namespace VSCL {
QtyRateRow::QtyRateRow(const QString& title, QtyRateDisplay* parent) : QGroupBox(title, parent) {
	parent->AddRow(this);
	Title = title;

	Organizer = new QHBoxLayout;
	Organizer->setContentsMargins(5, 5, 5, 5);
	setLayout(Organizer);

	QuantityLabel = new QLabel(this);
	QuantityLabel->setText(QString::number(Quantity) + QuantityUnits);
	Organizer->addWidget(QuantityLabel);
	RateLabel = new QLabel(this);
	RateLabel->setText(QString::number(Rate) + RateUnits);
	Organizer->addWidget(RateLabel);

	TitleFont = QFont();
	LabelFont = QFont();
	AdjustFontSize();
}

void QtyRateRow::resizeEvent(QResizeEvent* event) {
	QGroupBox::resizeEvent(event);
	AdjustFontSize();
}

void QtyRateRow::AdjustFontSize() {
	unsigned int tpt = static_cast<unsigned int>(TitleFontAdjustment.AdjustPxSize(window()));
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

