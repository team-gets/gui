#include <QGridLayout>

#include "NumericTestWidget.h"

namespace VSCL {

NumericTestWidget::NumericTestWidget(QWidget* parent, QWidget* whatToTest) {
	setParent(parent);

	QGridLayout* grid = new QGridLayout;
	setLayout(grid);

	TesterSpinbox = new QSpinBox;
	TesterSpinbox->setMinimum(0.0);
	TesterSpinbox->setMaximum(360.0);
	grid->addWidget(TesterSpinbox, 0, 0);

	WidgetBeingTested = whatToTest;
	grid->addWidget(WidgetBeingTested, 0, 1);
} // NumericTestWidget ctor

QSpinBox* NumericTestWidget::GetSpinbox() const { return TesterSpinbox; }
QWidget* NumericTestWidget::GetTestedWidget() const { return WidgetBeingTested; }

} // namespace VSCL
