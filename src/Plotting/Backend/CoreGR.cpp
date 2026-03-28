#include <cmath>

#include "gr.h"

#include "./CoreGR.h"
#include "./ColorGR.h"

namespace VSCL::Plot {

PlotGR::PlotGR(QWidget* parent) : GRWidget(parent) {
	SetWidgetRep(this);
};

void PlotGR::SetAxis(const Axis axis, const AxisInfo& info) { EmbeddablePlot2D::SetAxis(axis, info); draw(); }
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
	if (oversized)
		stepSize = static_cast<int>(std::floor(vecSize / arrSize));

	for (unsigned int i = 0; i < arrSize + endDelta; i += stepSize) {
		output[i] = original[i];
	}

	if (oversized)
		output[arrSize - 1] = original[arrSize - 1];

	return 0;
}

void PlotGR::UpdateAxes() {
	// Horizontal Axis {{{
	const AxisInfo& taxe = GetAxisInfoView(Axis::Time);
	double ttick = gr_tick(taxe.Range[0], taxe.Range[1]);
	AxisScaling tscal = taxe.Scaling;

	switch (tscal) {
	case AxisScaling::Log10:
		gr_setscale(GR_OPTION_X_LOG);
		break;
	case AxisScaling::Ln:
		gr_setscale(GR_OPTION_X_LN);
		break;
	case AxisScaling::Inverted:
		gr_setscale(GR_OPTION_FLIP_X);
		break;
	case AxisScaling::Linear:
	default:
		gr_setscale(0);
		break;
	}
	// }}}
	// Vertical Axis {{{
	const AxisInfo& qaxe = GetAxisInfoView(Axis::Quantity);
	double qtick = gr_tick(qaxe.Range[0], qaxe.Range[1]);
	AxisScaling qscal = qaxe.Scaling;

	switch (qscal) {
	case AxisScaling::Log10:
		gr_setscale(GR_OPTION_Y_LOG);
		break;
	case AxisScaling::Ln:
		gr_setscale(GR_OPTION_Y_LN);
		break;
	case AxisScaling::Inverted:
		gr_setscale(GR_OPTION_FLIP_Y);
		break;
	case AxisScaling::Linear:
	default:
		gr_setscale(0);
		break;
	}
	// }}}

	if (GetDrawGridState()) {
		gr_setlinecolorind(ColorIndex(ColorGR::Grey));
		gr_setlinetype(1);
		gr_grid(ttick, qtick, 0, 0, taxe.MajorSpacing, qaxe.MajorSpacing);
	}

	gr_setlinecolorind(ColorIndex(ColorGR::Black));
	gr_setlinetype(1);
    gr_axes(ttick, qtick, 0, 0, taxe.MajorSpacing, qaxe.MajorSpacing, -0.01);
} // void PlotGR::UpdateAxes();

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

		// Appearance and drawing
		switch (series.Style) {
		case LineStyle::Dashed:
			gr_setlinetype(2); // LINETYPE_DASHED
			break;
		case LineStyle::Dotted:
			gr_setlinetype(3); // LINETYPE_DOTTED
			break;
		case LineStyle::Solid:
		default:
			gr_setlinetype(1); // LINETYPE_SOLID
			break;
		}

		ColorGR color = ColorGRFromRGB(series.Color);
		gr_setlinecolorind(ColorIndex(color));
		gr_polyline(n, timeArr, quantityArr);
	}
} // void PlotGR::UpdateSeries()

void PlotGR::draw() {
	const AxisInfo& taxe = GetAxisInfoView(Axis::Time);
	const AxisInfo& qaxe = GetAxisInfoView(Axis::Quantity);

	double wxh = (double)width() / (double)height();
	double hxw = (double)height() / (double)width();
	double inset[4] = { 0.1, 0.97, 0.16, 0.9 }; // this is magic numbers
	double wwsdims[4] = { 0, 1, 0, 1 };
	double vpdims[4];

	if (width() > height()) {
		wwsdims[3] = hxw;
		double dims[4] = { inset[0], inset[1], inset[2]*hxw, inset[3]*hxw };
		memcpy(vpdims, dims, 4*sizeof(double));
	}
	else {
		wwsdims[1] = wxh;
		double dims[4] = { inset[0]*wxh, inset[1]*wxh, inset[2], inset[3] };
		memcpy(vpdims, dims, 4*sizeof(double));
	}

	gr_setwswindow(wwsdims[0], wwsdims[1], wwsdims[2], wwsdims[3]);
	gr_setviewport(vpdims[0], vpdims[1], vpdims[2], vpdims[3]);
	gr_setwindow(taxe.Range[0], taxe.Range[1], qaxe.Range[0], qaxe.Range[1]);

	UpdateSeries();
	UpdateAxes();
}
} // namespace VSCL::Plot
// vim: foldmethod=marker
