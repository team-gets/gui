#pragma once

#include <QtWidgets>

namespace VSCL {
class NumericTestWidget : public QWidget {

	Q_OBJECT;

public:
	NumericTestWidget(QWidget* parent, QWidget* whatToTest);

private:
	QSpinBox* TesterSpinbox;
	QWidget* WidgetBeingTested;

public:
	QSpinBox* GetSpinbox() const;
	QWidget* GetTestedWidget() const;

}; // class NumericTestWidget
} // namespace VSCL
