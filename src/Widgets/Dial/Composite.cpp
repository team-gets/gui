#include "Composite.hpp"

namespace VSCL {

CompositeDial::CompositeDial(QWidget* parent)
	: QWidget(parent)
	, MajorOrganizer(new QGridLayout(this))
	, DialNameLabel(new QLabel(this))
	, DialRateDuo(new QWidget(this))
	, DuoOrganizer(new QGridLayout(DialRateDuo))
	, Dial(new AttitudeDial(DialRateDuo))
	, NumericRateLabel(new RateLabel(DialRateDuo)) {

	// Widget setup goes top -> bottom level
	// Top-level
	this->setLayout(MajorOrganizer);
	this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	MajorOrganizer->addWidget(DialNameLabel, 0, 0, 1, 1);
	MajorOrganizer->addWidget(DialRateDuo, 1, 0, 5, 1);

	MajorOrganizer->setAlignment(Qt::AlignHCenter);
	MajorOrganizer->setAlignment(DialNameLabel, Qt::AlignHCenter | Qt::AlignTop);

	DialNameLabel->setText("Dial");
	DialNameLabel->setScaledContents(true);
	DialNameLabel->setFont(DialNameFont);
	DialNameLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
	DialNameLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

	// Bottom-level
	DialRateDuo->setLayout(DuoOrganizer);

	DuoOrganizer->addWidget(Dial, 0, 0);
	DuoOrganizer->addWidget(NumericRateLabel, 0, 0);

	QSizePolicy expandPolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	DuoOrganizer->setAlignment(NumericRateLabel, Qt::AlignHCenter | Qt::AlignVCenter);
	DialRateDuo->setSizePolicy(expandPolicy);
	Dial->setSizePolicy(expandPolicy);
}

CompositeDial::CompositeDial(const QString& title, QWidget* parent)
	: CompositeDial(parent) {
	DialNameLabel->setText(title);
}

void CompositeDial::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);

	DialNameFont.setPixelSize(TitleAdjustment.AdjustPxSize(window()));
	DialNameLabel->setFont(DialNameFont);
	NumericRateLabel->resizeEvent(event);
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
