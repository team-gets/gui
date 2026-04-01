#include <QGridLayout>

#include "NumericTestWidget.hpp"

namespace VSCL {

NumericTestWidget::NumericTestWidget(
		QWidget* parent, QWidget* whatToTest,
		std::function<void(int)> method)
	: QWidget(parent)
	, TesterSpinbox(new QDoubleSpinBox(this))
	, WidgetBeingTested(whatToTest) {

	QGridLayout* grid = new QGridLayout(this);
	grid->setContentsMargins(25, 25, 25, 25);
	grid->addWidget(TesterSpinbox, 0, 0);
	grid->addWidget(WidgetBeingTested, 0, 1);
	setLayout(grid);

	TesterSpinbox->setRange(0.0, 360.0);
	TesterSpinbox->setSuffix("°");
	TesterSpinbox->setWrapping(true);

	QSizePolicy sizePolicy;
	sizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
	sizePolicy.setVerticalPolicy(QSizePolicy::Expanding);

	WidgetBeingTested->setSizePolicy(sizePolicy);

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
