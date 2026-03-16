#include "QuantitiesRatesRow.h"
#include "QuantitiesRatesDisplay.h"

namespace VSCL {
QtyRateRow::QtyRateRow(QtyRateDisplay* parent) : QFrame(parent) {
	parent->AddRow(this);
}

void QtyRateRow::SetQuantity(double newQuantity) { Quantity = newQuantity; }
void QtyRateRow::SetRate(double newRate) { Rate = newRate; }

} // namespace VSCL

