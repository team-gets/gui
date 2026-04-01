#include "QuantitiesRatesDisplay.hpp"
#include "QuantitiesRatesRow.hpp"

namespace VSCL {

QtyRateDisplay::QtyRateDisplay(const QString& title, QWidget* parent)
	: QGroupBox(title, parent) {
	Organizer = new QVBoxLayout;
	Organizer->setContentsMargins(10, 10, 10, 10);
	setLayout(Organizer);
};

const QList<QtyRateRow*>& QtyRateDisplay::GetRowsView() const { return Rows; }
void QtyRateDisplay::AddRow(QtyRateRow* newRow) { Rows.append(newRow); Organizer->addWidget(newRow); }

} // namespace VSCL
