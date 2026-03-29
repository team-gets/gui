#include <cassert>
#include <array>

#include "RateLabel.hpp"
#include "Util/FiniteDiff.hpp"

namespace VSCL {

RateLabel::RateLabel(QWidget* parent) : QLabel(parent) {
	SetTextFrom(0.0);
	setScaledContents(true);
}

void RateLabel::SetTextFrom(double num) {
	setText(QString::number(num) + QuantityUnitString + TimeUnitString);
}

void RateLabel::SetRateFromArray(const std::vector<double>& ts, const std::vector<double>& qtys) {
	size_t tsz = ts.size();
	size_t qsz = qtys.size();

	if (tsz < 3) { return; };
	if (qsz < 3) { return; };

	const std::array<double, 3> tst = { ts[tsz - 1], ts[tsz - 2], ts[tsz - 3] };
	const std::array<double, 3> qst = { qtys[qsz - 1], qtys[qsz - 2], qtys[qsz - 3] };
	Rate = Util::CenterFiniteDifference(tst, qst);
}

void RateLabel::DisplayRateFromArray(const std::vector<double>& ts, const std::vector<double>& qtys) {
	SetRateFromArray(ts, qtys);
	SetTextFrom(Rate);
}
} // namespace VSCL
