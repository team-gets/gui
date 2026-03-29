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
	DialNameLabel->setSizePolicy(expandPolicy);

	MajorOrganizer->setAlignment(Qt::AlignHCenter);
	MajorOrganizer->setAlignment(DialNameLabel, Qt::AlignHCenter | Qt::AlignTop);
	//MajorOrganizer->setAlignment(DialRateDuo, Qt::AlignHCenter);

	//DuoOrganizer->setAlignment(Qt::AlignHCenter);
	//DuoOrganizer->setAlignment(Dial,Qt::AlignHCenter);
	DuoOrganizer->setAlignment(NumericRateLabel, Qt::AlignHCenter);
}

CompositeDial::CompositeDial(const QString& title, QWidget* parent)
	: CompositeDial(parent) {
	DialNameLabel->setText(title);
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
