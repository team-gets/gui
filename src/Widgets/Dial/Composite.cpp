#include "Composite.hpp"

namespace VSCL {

CompositeDial::CompositeDial(QWidget* parent) : QWidget(parent) {
	DialNameLabel = new class QLabel(this);
	Dial = new class AttitudeDial(this);
	RateLabel = new class RateLabel(this);

	DialNameLabel->setText("Dial");

	Organizer = new class QGridLayout(this);
	setLayout(Organizer);

	Organizer->addWidget(DialNameLabel, 0, 0);
	Organizer->addWidget(Dial, 1, 0);
	Organizer->addWidget(RateLabel, 1, 0);
}

CompositeDial::CompositeDial(const QString& title, QWidget* parent)
	: CompositeDial(parent) {
	DialNameLabel->setText(title);
}

// Wrap accessors and settors around child widgets {{{
void CompositeDial::SetDialTitle(const QString& title) { DialNameLabel->setText(title); }
void CompositeDial::SetDialAngle(double value) { Dial->SetDialAngle(value); }
void CompositeDial::DisplayRateFromArray(
	const std::vector<double>& ts, const std::vector<double>& qtys) {
		RateLabel->DisplayRateFromArray(ts, qtys); }
// }}}
} // namespace VSCL
// vim: foldmethod=marker
