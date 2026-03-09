#include <QGridLayout>

#include "NumericTestWidget.h"

namespace VSCL {

NumericTestWidget::NumericTestWidget(
		QWidget* parent, QWidget* whatToTest,
		std::function<void(int)> method) : QWidget(parent) {

	setParent(parent);

	QGridLayout* grid = new QGridLayout;
	setLayout(grid);

	TesterSpinbox = new QDoubleSpinBox;
	TesterSpinbox->setMinimum(0.0);
	TesterSpinbox->setMaximum(360.0);

	connect(TesterSpinbox, &QDoubleSpinBox::valueChanged, whatToTest, method);

	grid->addWidget(TesterSpinbox, 0, 0);

	WidgetBeingTested = whatToTest;
	grid->addWidget(WidgetBeingTested, 0, 1);
} // NumericTestWidget ctor

QDoubleSpinBox* NumericTestWidget::GetSpinbox() const { return TesterSpinbox; }
QWidget* NumericTestWidget::GetTestedWidget() const { return WidgetBeingTested; }

} // namespace VSCL
