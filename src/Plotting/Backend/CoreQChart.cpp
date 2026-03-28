#include <iostream>
#include <algorithm>
#include "CoreQChart.h"

namespace VSCL::Plot {

PlotQChart::PlotQChart(QWidget* parent) : QChartView(parent) {
	SetWidgetRep(this);

	PlotChart = new QChart;
	TimeAxisQt = new QValueAxis;
	QuantityAxisQt = new QValueAxis;

	PlotChart->addAxis(TimeAxisQt, Qt::AlignBottom);
	SetAxis(Axis::Time, GetAxisInfoView(Axis::Time));

	PlotChart->addAxis(QuantityAxisQt, Qt::AlignLeft);
	SetAxis(Axis::Quantity, GetAxisInfoView(Axis::Quantity));

	PlotChart->legend()->setVisible(false);
	PlotChart->setTheme(QChart::ChartThemeLight);
	setChart(PlotChart);
}

PlotQChart::~PlotQChart() {
	if (PlotChart)
		delete PlotChart;
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
	default:
		axqt = QuantityAxisQt;
		break;
	}

	if (!axqt) { return; };
	axqt->setRange(ax.Range[0], ax.Range[1]);
	axqt->setTickInterval(ax.MajorSpacing);
}

void PlotQChart::SetTitle(const std::string& title) {
	EmbeddablePlot2D::SetTitle(title);
	PlotChart->setTitle(QString::fromStdString(title));
}

void PlotQChart::Plot() {
	EmbeddablePlot2D::Plot();

	const std::vector<SeriesInfo>& sinfos = GetSeriesInfosView();
	unsigned int idx = 0;
	if (sinfos.size() < 0) { return; }

	for (QAbstractSeries* aseriesQt : PlotChart->series()) {
		if (!aseriesQt) { return; }

		QXYSeries* serie = qobject_cast<QXYSeries*>(aseriesQt);
		if (!serie) { return; }

		QList<QPointF> pts;
		const SeriesInfo& sinfo = sinfos[idx];
		unsigned int n = sinfo.Times.size();
		if (n == 0) { continue; }

		for (unsigned int i = 0; i < n; i++) {
			pts.append({ sinfo.Times[i], sinfo.Quantities[i] });
		}

		serie->replace(pts);
		idx++;
	}
}

void PlotQChart::EraseAllData() {
	EmbeddablePlot2D::EraseAllData();
}

void PlotQChart::AddSeries(const SeriesInfo& newInfo) {
	EmbeddablePlot2D::AddSeries(newInfo);

	QLineSeries* newSeries = new QLineSeries(PlotChart);
	PlotChart->addSeries(newSeries);
	if (!newSeries->attachAxis(TimeAxisQt)) { return; };
	if (!newSeries->attachAxis(QuantityAxisQt)) { return; };

	Plot();
}
} // namespace VSCL::Plot
