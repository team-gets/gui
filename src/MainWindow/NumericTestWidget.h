#pragma once

#include <QtWidgets>
#include <QGridLayout>

namespace VSCL {
class NumericTestWidget : public QWidget {

	Q_OBJECT;

public:
	NumericTestWidget(QWidget* parent, QWidget* whatToTest);

private:
	QGridLayout* Grid;
	QSpinBox* TesterSpinbox;
	QWidget* WidgetBeingTested;

public:
	QGridLayout* GetGrid() const;
	QSpinBox* GetSpinbox() const;
	QWidget* GetTestedWidget() const;

}; // class NumericTestWidget
} // namespace VSCL
