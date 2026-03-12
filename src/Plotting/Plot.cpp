#include <QHBoxLayout>
#include "Plot.h"

namespace VSCL::Plot {

void EmbeddablePlot::AddPoint(unsigned int idx,
		double time, double quantity) {
	std::vector<double>& oldTime = Series[idx].Times;
	std::vector<double>& oldQty = Series[idx].Quantities;

	oldTime.push_back(time);
	oldQty.push_back(quantity);
}
void EmbeddablePlot::AddPoint(
		double time, double quantity) {
			AddPoint(0, time, quantity); }

void EmbeddablePlot::AddPoints(unsigned int idx,
		const std::vector<double>& times, const std::vector<double>& quantities) {
	std::vector<double>& oldTime = Series[idx].Times;
	std::vector<double>& oldQty = Series[idx].Quantities;

	oldTime.resize(oldTime.size() + times.size());
	oldQty.resize(oldQty.size() + quantities.size());

	for (double time : times) {
		oldTime.push_back(time);
	}

	for (double quantity : quantities) {
		oldQty.push_back(quantity);
	}
}
void EmbeddablePlot::AddPoints(
		const std::vector<double>& times, const std::vector<double>& quantities) {
			AddPoints(0, times, quantities); }

void EmbeddablePlot::SetAxis(Axis axis, AxisInfo& info) {
	switch (axis) {
	case Axis::Time:
		TimeAxis = info;
		break;
	case Axis::Quantity:
		QuantityAxis = info;
		break;
	}
}

void EmbeddablePlot::SetTitle(const std::string& title) { Title = title; }

void EmbeddablePlot::Plot() {
	if (WidgetRep)
		WidgetRep->update();
}

void EmbeddablePlot::EraseAllData() {
	for (SeriesInfo& series : Series) {
		series.Times.clear();
		series.Quantities.clear();
	}
}

std::vector<double> EmbeddablePlot::GetTimes(unsigned int idx) const { return Series[idx].Times; }
std::vector<double> EmbeddablePlot::GetTimes() const { return GetTimes(0); }
std::vector<double> EmbeddablePlot::GetQuantities(unsigned int idx) const { return Series[idx].Quantities; }
std::vector<double> EmbeddablePlot::GetQuantities() const { return GetQuantities(0); }
QWidget* EmbeddablePlot::GetWidgetRep() const { return WidgetRep; }
void EmbeddablePlot::SetWidgetRep(QWidget* newWidgetRep) { WidgetRep = newWidgetRep; }

} // namespace VSCL::Plot
