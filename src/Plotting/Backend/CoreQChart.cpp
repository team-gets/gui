#include "CoreQChart.h"

namespace VSCL::Plot {

PlotQChart::PlotQChart(QWidget* parent) : QChartView(parent) {
	SetWidgetRep(this);

	PlotChart = new QChart;
	QTimeAxis = new QValueAxis;
	QQuantityAxis = new QValueAxis;

	QLineSeries* firstSeries = new QLineSeries;
	QLineSerieses.append(firstSeries);

	PlotChart->addAxis(QTimeAxis, Qt::AlignBottom);
	PlotChart->addAxis(QQuantityAxis, Qt::AlignLeft);
	PlotChart->setTheme(QChart::ChartThemeLight);
	setChart(PlotChart);
}
PlotQChart::~PlotQChart() {
	delete PlotChart;
	for (QLineSeries* serie : QLineSerieses) {
		delete serie;
	}
}

void PlotQChart::SetAxis(Axis axis, AxisInfo& info) {
	EmbeddablePlot2D::SetAxis(axis, info);
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