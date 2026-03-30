#include "Composite.hpp"

namespace VSCL {

CompositeDial::CompositeDial(QWidget* parent) : QWidget(parent) {
	// Child widget setup goes top -> bottom level

	MajorOrganizer = new QGridLayout(this);
	this->setLayout(MajorOrganizer);

	DialNameLabel = new QLabel(this);
	DialRateDuo = new QWidget(this);

	DialNameLabel->setText("Dial");
	DialNameLabel->setScaledContents(true);
	DialNameLabel->setFont(DialNameFont);

	MajorOrganizer->addWidget(DialNameLabel, 0, 0, 1, 1);
	MajorOrganizer->addWidget(DialRateDuo, 1, 0, 5, 1);

	DuoOrganizer = new QGridLayout(DialRateDuo);
	DialRateDuo->setLayout(DuoOrganizer);

	Dial = new AttitudeDial(DialRateDuo);
	NumericRateLabel = new RateLabel(DialRateDuo);

	DuoOrganizer->addWidget(Dial, 0, 0);
	DuoOrganizer->addWidget(NumericRateLabel, 0, 0);

	QSizePolicy expandPolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	this->setSizePolicy(expandPolicy);
	DialRateDuo->setSizePolicy(expandPolicy);
	Dial->setSizePolicy(expandPolicy);

	QSizePolicy vertConstrain(QSizePolicy::Preferred, QSizePolicy::Minimum);
	DialNameLabel->setSizePolicy(vertConstrain);

	MajorOrganizer->setAlignment(Qt::AlignHCenter);
	MajorOrganizer->setAlignment(DialNameLabel, Qt::AlignHCenter | Qt::AlignTop);

	DuoOrganizer->setAlignment(NumericRateLabel, Qt::AlignHCenter | Qt::AlignVCenter);
}

CompositeDial::CompositeDial(const QString& title, QWidget* parent)
	: CompositeDial(parent) {
	DialNameLabel->setText(title);
}

void CompositeDial::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);

	DialNameFont.setPointSize(TitleAdjustment.AdjustPointSize(window()));
	DialNameLabel->setFont(DialNameFont);
}

// Wrap accessors and settors of child widgets {{{
void CompositeDial::SetDialTitle(const QString& title) { DialNameLabel->setText(title); }
void CompositeDial::SetDialAngle(double value) { Dial->SetDialAngle(value); }
void CompositeDial::DisplayRateFromArray(
	const std::vector<double>& ts, const std::vector<double>& qtys) {
		NumericRateLabel->DisplayRateFromArray(ts, qtys); }
// }}}
} // namespace VSCL
// vim: foldmethod=marker
