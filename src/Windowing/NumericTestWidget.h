#pragma once

#include <QtWidgets>
#include <functional>

namespace VSCL {
class NumericTestWidget : public QWidget {

	Q_OBJECT;

public:
	NumericTestWidget(QWidget* parent, QWidget* whatToTest,
			std::function<void(int)> method);

	virtual void setVisible(bool visible) override;

private:
	QDoubleSpinBox* TesterSpinbox;
	QWidget* WidgetBeingTested;

public:
	QDoubleSpinBox* GetSpinbox() const;
	QWidget* GetTestedWidget() const;

}; // class NumericTestWidget
} // namespace VSCL
