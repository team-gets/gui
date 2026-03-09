#include "NumericTestWidget.h"

namespace VSCL {

NumericTestWidget::NumericTestWidget(QWidget* parent, QWidget* whatToTest) {
	this->setParent(parent);

	Grid = new QGridLayout;
	setLayout(Grid);

	TesterSpinbox = new QSpinBox;
	Grid->addWidget(TesterSpinbox, 0, 0);

	WidgetBeingTested = whatToTest;
	Grid->addWidget(WidgetBeingTested, 0, 1);
} // NumericTestWidget ctor

QGridLayout* NumericTestWidget::GetGrid() const { return Grid; }
QSpinBox* NumericTestWidget::GetSpinbox() const { return TesterSpinbox; }
QWidget* NumericTestWidget::GetTestedWidget() const { return WidgetBeingTested; }

} // namespace VSCL
