#include "QuantitiesRatesDisplay.hpp"
#include "QuantitiesRatesRow.hpp"

namespace VSCL {

QtyRateDisplay::QtyRateDisplay(const QString& title, QWidget* parent)
	: QGroupBox(title, parent)
	, Organizer(new QVBoxLayout(this)) {
	Organizer->setContentsMargins(10, 10, 10, 10);
	setLayout(Organizer);
};

const QList<QtyRateRow*>& QtyRateDisplay::GetRowsView() const { return Rows; }
void QtyRateDisplay::AddRow(QtyRateRow* new_row) { Rows.append(new_row); Organizer->addWidget(new_row); }

} // namespace VSCL
