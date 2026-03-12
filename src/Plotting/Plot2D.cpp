#include <QHBoxLayout>
#include "Plot2D.h"

namespace VSCL::Plot {

void EmbeddablePlot2D::AddPoint(uint8_t idx,
		double time, double quantity) {
	std::vector<double>& oldTime = Series[idx].Times;
	std::vector<double>& oldQty = Series[idx].Quantities;

	oldTime.push_back(time);
	oldQty.push_back(quantity);
}
void EmbeddablePlot2D::AddPoint(
		double time, double quantity) {
			AddPoint(0, time, quantity); }

void EmbeddablePlot2D::AddPoints(uint8_t idx,
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
void EmbeddablePlot2D::AddPoints(
		const std::vector<double>& times, const std::vector<double>& quantities) {
			AddPoints(0, times, quantities); }

void EmbeddablePlot2D::SetAxis(Axis axis, AxisInfo& info) {
	switch (axis) {
	case Axis::Time:
		TimeAxis = info;
		break;
	case Axis::Quantity:
		QuantityAxis = info;
		break;
	}
}

void EmbeddablePlot2D::SetTitle(const std::string& title) { Title = title; }

void EmbeddablePlot2D::SetColor(uint8_t idx, ColorRGB& color) { Series[idx].Color = color; }
void EmbeddablePlot2D::SetColor(ColorRGB& color) { SetColor(0, color); }

void EmbeddablePlot2D::Plot() {
	if (WidgetRep)
		WidgetRep->update();
}

void EmbeddablePlot2D::EraseAllData() {
	for (SeriesInfo& series : Series) {
		series.Times.clear();
		series.Quantities.clear();
	}
}

std::vector<double> EmbeddablePlot2D::GetTimes(uint8_t idx) const { return Series[idx].Times; }
std::vector<double> EmbeddablePlot2D::GetTimes() const { return GetTimes(0); }
std::vector<double> EmbeddablePlot2D::GetQuantities(uint8_t idx) const { return Series[idx].Quantities; }
std::vector<double> EmbeddablePlot2D::GetQuantities() const { return GetQuantities(0); }

const AxisInfo& EmbeddablePlot2D::GetAxisInfoView(Axis axis) const {
	switch (axis) {
	case Axis::Time:
		return TimeAxis;
		break;
	case Axis::Quantity:
	default:
		return QuantityAxis;
		break;
	};
};

QWidget* EmbeddablePlot2D::GetWidgetRep() const { return WidgetRep; }
void EmbeddablePlot2D::SetWidgetRep(QWidget* newWidgetRep) { WidgetRep = newWidgetRep; }

} // namespace VSCL::Plot
