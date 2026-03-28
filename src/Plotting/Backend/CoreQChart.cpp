#include <iostream>
#include <algorithm>
#include "CoreQChart.h"

namespace VSCL::Plot {

PlotQChart::PlotQChart(QWidget* parent) : QChartView(parent) {
	SetWidgetRep(this);

	PlotChart = new QChart;
	TimeAxisQt = new QValueAxis;
	QuantityAxisQt = new QValueAxis;

	SetAxis(Axis::Time, GetAxisInfoView(Axis::Time));
	PlotChart->addAxis(TimeAxisQt, Qt::AlignBottom);

	SetAxis(Axis::Quantity, GetAxisInfoView(Axis::Quantity));
	PlotChart->addAxis(QuantityAxisQt, Qt::AlignLeft);

	QLineSeries* firstSeries = new QLineSeries;
	PlotChart->addSeries(firstSeries);
	LineSeriesesQt.append(firstSeries);
	
	if (!firstSeries->attachAxis(TimeAxisQt)) { std::cerr << "Time axis attachment failure\n"; };
	if (!firstSeries->attachAxis(QuantityAxisQt)) { std::cerr << "Quantity axis attachment failure\n"; };

	PlotChart->setTheme(QChart::ChartThemeLight);
	setChart(PlotChart);
}

PlotQChart::~PlotQChart() {
	if (PlotChart)
		delete PlotChart;

	for (const QLineSeries* seriesqt : LineSeriesesQt) {
		if (seriesqt)
			delete seriesqt;
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

	const std::vector<SeriesInfo>& sinfos = GetSeriesInfosView();
	unsigned int idx = 0;
	if (sinfos.size() < 0) return;

	std::for_each(sinfos.begin(), sinfos.end(),
		[&](const SeriesInfo& sinfo) {
			QLineSeries* serie = LineSeriesesQt[idx];
			QList<QPointF> pts;
			unsigned int n = sinfo.Times.size();
			if (n == 0) return;

			for (unsigned int i = 0; i < n; i++) {
				pts.append({ sinfo.Times[i], sinfo.Quantities[i] });
			}

			serie->replace(pts);
			idx++;
		});
}

void PlotQChart::EraseAllData() {
	EmbeddablePlot2D::EraseAllData();
}
} // namespace VSCL::Plot
