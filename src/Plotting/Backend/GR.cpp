#include <cmath>

#include "./GR.h"
#include "./ColorGR.h"
#include "gr.h"

namespace VSCL::Plot {

PlotGR::PlotGR(QWidget* parent) : GRWidget(parent) {
	SetWidgetRep(this);
};

void PlotGR::SetAxis(Axis axis, AxisInfo& info) { EmbeddablePlot2D::SetAxis(axis, info); draw(); }
void PlotGR::SetTitle(const std::string& title) { EmbeddablePlot2D::SetTitle(title); draw(); }

void PlotGR::Plot() {
	EmbeddablePlot2D::Plot();
	draw();
}

void PlotGR::EraseAllData() {
	EmbeddablePlot2D::EraseAllData();
	draw();
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

void PlotGR::UpdateAxes() {
	const AxisInfo& taxe = GetAxisInfoView(Axis::Time);
	double ttick = gr_tick(taxe.Range[0], taxe.Range[1]);
	AxisScaling tscal = taxe.Scaling;

	switch (tscal) {
	case AxisScaling::Logarithmic:
		gr_setscale(GR_OPTION_X_LOG);
		break;
	case AxisScaling::Linear:
	default:
		gr_setscale(0);
		break;
	}

	const AxisInfo& qaxe = GetAxisInfoView(Axis::Quantity);
	double qtick = gr_tick(qaxe.Range[0], qaxe.Range[1]);
	AxisScaling qscal = qaxe.Scaling;

	switch (qscal) {
	case AxisScaling::Logarithmic:
		gr_setscale(GR_OPTION_Y_LOG);
		break;
	case AxisScaling::Linear:
	default:
		gr_setscale(0);
		break;
	}

	gr_setlinecolorind(ColorIndex(ColorGR::Black));
    gr_axes(ttick, qtick, 0, 0, taxe.MajorSpacing, qaxe.MajorSpacing, -0.01);
}

void PlotGR::UpdateSeries() {
	const std::vector<SeriesInfo> serieses = GetSeriesInfosView();
	for (const SeriesInfo& series : serieses) {
		const std::vector<double> times = series.Times;
		const std::vector<double> quantities = series.Quantities;
		if (times.size() < 2 || quantities.size() < 2) { continue; }

		// Magic number 512 (arbitrary power of 2)
		const size_t vecSize = times.size();
		const size_t n = (vecSize < 512) ? vecSize : 512;

		double timeArr[512] = { 0.0 };
		double quantityArr[512] = { 0.0 };

		DoubleVectorToArray(times, timeArr, n);
		DoubleVectorToArray(quantities, quantityArr, n);

		gr_setlinecolorind(ColorIndex(ColorGRFromRGB(series.Color)));
		gr_polyline(n, timeArr, quantityArr);
	}
}

void PlotGR::draw() {
	UpdateAxes();
	UpdateSeries();
}
} // namespace VSCL::Plot
