#pragma once

#include <QtWidgets>
#include <functional>

namespace VSCL {
class NumericTestWidget : public QWidget {

	Q_OBJECT;

public:
	NumericTestWidget(QWidget* parent, QWidget* whatToTest,
			std::function<void(int)> method);

private:
	QSpinBox* TesterSpinbox;
	QWidget* WidgetBeingTested;

public:
	QSpinBox* GetSpinbox() const;
	QWidget* GetTestedWidget() const;

}; // class NumericTestWidget
} // namespace VSCL
