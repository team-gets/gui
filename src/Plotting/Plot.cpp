#include <QHBoxLayout>
#include "Plot.h"

namespace VSCL::Plot {

void EmbeddablePlot::AddPoint(const double time, const double quantity) {
	Times.push_back(time);
	Quantities.push_back(quantity);
}

void EmbeddablePlot::AddPoints(const std::vector<double>& times, const std::vector<double>& quantities) {
	Times.resize(Times.size() + times.size());
	Quantities.resize(Quantities.size() + quantities.size());

	for (const double time : times) {
		Times.push_back(time);
	}

	for (const double quantity : quantities) {
		Quantities.push_back(quantity);
	}
}

void EmbeddablePlot::Plot() {
	if (WidgetRep)
		WidgetRep->update();
}

void EmbeddablePlot::EraseAllData() {
	Times.clear();
	Quantities.clear();
}

std::vector<double> EmbeddablePlot::GetTimes() const { return Times; }
std::vector<double> EmbeddablePlot::GetQuantities() const { return Quantities; }
QWidget* EmbeddablePlot::GetWidgetRep() const { return WidgetRep; }
void EmbeddablePlot::SetWidgetRep(QWidget* newWidgetRep) { WidgetRep = newWidgetRep; }

} // namespace VSCL::Plot
