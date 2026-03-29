#pragma once

#include <QtWidgets>

namespace VSCL {

class QtyRateRow;

class QtyRateDisplay : public QGroupBox {
	
	Q_OBJECT;
	friend class QtyRateRow;

public:
	QtyRateDisplay(const QString& title, QWidget* parent = nullptr);

	const QList<QtyRateRow*>& GetRowsView() const;

protected:
	void AddRow(QtyRateRow* newRow);

private:
	QList<QtyRateRow*> Rows;

	QVBoxLayout* Organizer;

}; // class QtyRateDisplay
} // namespace VSCL
