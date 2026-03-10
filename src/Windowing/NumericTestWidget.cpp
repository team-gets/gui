#include <QGridLayout>

#include "NumericTestWidget.h"

namespace VSCL {

NumericTestWidget::NumericTestWidget(
		QWidget* parent, QWidget* whatToTest,
		std::function<void(int)> method) : QWidget(parent) {

	setParent(parent);

	QGridLayout* grid = new QGridLayout;
	grid->setContentsMargins(25, 25, 25, 25);
	setLayout(grid);

	TesterSpinbox = new QDoubleSpinBox;
	TesterSpinbox->setRange(0.0, 360.0);
	TesterSpinbox->setSuffix("°");
	TesterSpinbox->setWrapping(true);
	grid->addWidget(TesterSpinbox, 0, 0);

	QSizePolicy sizePolicy;
	sizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
	sizePolicy.setVerticalPolicy(QSizePolicy::Expanding);

	WidgetBeingTested = whatToTest;
	WidgetBeingTested->setSizePolicy(sizePolicy);
	grid->addWidget(WidgetBeingTested, 0, 1);

	connect(TesterSpinbox, &QDoubleSpinBox::valueChanged, WidgetBeingTested, method);
} // NumericTestWidget ctor

void NumericTestWidget::setVisible(bool visible) {
	TesterSpinbox->setVisible(visible);
	WidgetBeingTested->setVisible(visible);
	QWidget::setVisible(visible);
}

QDoubleSpinBox* NumericTestWidget::GetSpinbox() const { return TesterSpinbox; }
QWidget* NumericTestWidget::GetTestedWidget() const { return WidgetBeingTested; }

} // namespace VSCL
