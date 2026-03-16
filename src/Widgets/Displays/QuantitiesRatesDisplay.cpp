#include "QuantitiesRatesDisplay.h"
#include "QuantitiesRatesRow.h"

namespace VSCL {

QtyRateDisplay::QtyRateDisplay(QWidget* parent) : QGroupBox(parent) {
	Organizer = new QVBoxLayout;
	Organizer->setContentsMargins(10, 10, 10, 10);
	setLayout(Organizer);
};

const QList<QtyRateRow*>& QtyRateDisplay::GetRowsView() const { return Rows; }
void QtyRateDisplay::AddRow(QtyRateRow* newRow) { Rows.append(newRow); Organizer->addWidget(newRow); }

} // namespace VSCL
