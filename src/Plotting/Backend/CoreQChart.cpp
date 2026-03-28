#include "CoreQChart.h"

namespace VSCL::Plot {

PlotQChart::PlotQChart(QWidget* parent) : QChartView(parent) {
	SetWidgetRep(this);

	PlotChart = new QChart;
	TimeAxisQt = new QValueAxis;
	QuantityAxisQt = new QValueAxis;

	QLineSeries* firstSeries = new QLineSeries;
	QLineSerieses.append(firstSeries);

	SetAxis(Axis::Time, GetAxisInfoView(Axis::Time));
	PlotChart->addAxis(TimeAxisQt, Qt::AlignBottom);

	SetAxis(Axis::Quantity, GetAxisInfoView(Axis::Quantity));
	PlotChart->addAxis(QuantityAxisQt, Qt::AlignLeft);

	PlotChart->setTheme(QChart::ChartThemeLight);
	setChart(PlotChart);
}
PlotQChart::~PlotQChart() {
	if (PlotChart)
		delete PlotChart;

	for (QLineSeries* serie : QLineSerieses) {
		if (serie)
			delete serie;
	}
}

void PlotQChart::SetAxis(const Axis axis, const AxisInfo& info) {
	EmbeddablePlot2D::SetAxis(axis, info);
	const AxisInfo& ax = GetAxisInfoView(axis);
	QValueAxis* axqt;

	switch (axis) {
	case Axis::Time:
		axqt = TimeAxisQt;
		break;
	case Axis::Quantity:
		axqt = QuantityAxisQt;
		break;
	}

	axqt->setRange(ax.Range[0], ax.Range[1]);
	axqt->setTickInterval(ax.MajorSpacing);
}

void PlotQChart::SetTitle(const std::string& title) {
	EmbeddablePlot2D::SetTitle(title);
	PlotChart->setTitle(QString::fromStdString(title));
}

void PlotQChart::Plot() {
	EmbeddablePlot2D::Plot();
}

void PlotQChart::EraseAllData() {
	EmbeddablePlot2D::EraseAllData();
}
} // namespace VSCL::Plot
