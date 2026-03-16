#pragma once

#include <QtWidgets>

namespace VSCL {

class QuantitiesRatesRow;

class QuantitesRatesDisplay : public QFrame {
	
	Q_OBJECT;
	friend class QuantitesRatesRow;

public:
	QuantitesRatesDisplay(QWidget* parent = nullptr);

	const QList<QuantitiesRatesRow*>& GetRowsView() const;

protected:
	void AddRow(QuantitiesRatesRow* newRow);

private:
	QList<QuantitiesRatesRow*> Rows;

}; // class QuantitiesRatesDisplay
} // namespace VSCL
