#include <cmath>

#include "./GR.h"
#include "gr.h"

namespace VSCL::Plot {

PlotGR::PlotGR(QWidget* parent) : GRWidget(parent) {
	SetWidgetRep(this);
};

void PlotGR::SetAxis(Axis axis, AxisInfo& info) { EmbeddablePlot2D::SetAxis(axis, info); }
void PlotGR::SetTitle(const std::string& title) { EmbeddablePlot2D::SetTitle(title); }

void PlotGR::Plot() {
	EmbeddablePlot2D::Plot();
	draw();
}

void PlotGR::EraseAllData() {
	EmbeddablePlot2D::EraseAllData();
}

int PlotGR::DoubleVectorToArray(const std::vector<double>& original,
		double* output, const size_t arrSize) {

	const size_t vecSize = original.size();
	const bool oversized = vecSize > arrSize;

	int stepSize = 1;
	int endDelta = (oversized) ? -1 : 0;
	// End delta will change so that it's inclusive of the last point

	// Must take samplings if it's too big to fit
	if (oversized) {
		stepSize = static_cast<int>(std::floor(vecSize / arrSize));
		qDebug() << "I AM HUGE\n" ;
	}

	for (unsigned int i = 0; i < arrSize + endDelta; i += stepSize) {
		output[i] = original[i];
	}

	if (oversized)
		output[arrSize - 1] = original[arrSize - 1];

	return 0;
}

void PlotGR::draw() {
	const std::vector<double> times = GetTimes(0);
	const std::vector<double> quantities = GetQuantities(0);
	if (times.size() < 2 || quantities.size() < 2) { return; }

	// Magic number 512 (arbitrary power of 2)
	const size_t vecSize = times.size();
	const size_t n = (vecSize < 512) ? vecSize : 512;

	double timeArr[512] = { 0.0 };
	double quantityArr[512] = { 0.0 };

	DoubleVectorToArray(times, timeArr, n);
	DoubleVectorToArray(quantities, quantityArr, n);

	gr_setlinecolorind(ColorIndex(ColorGR::Red));
	gr_polyline(n, timeArr, quantityArr);
	gr_setlinecolorind(ColorIndex(ColorGR::Black));
    gr_axes(gr_tick(0, 1), gr_tick(0, 1), 0, 0, 1, 1, -0.01);
}
} // namespace VSCL::Plot
