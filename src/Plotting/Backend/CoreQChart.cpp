#include <iostream>
#include <algorithm>
#include "CoreQChart.h"

namespace VSCL::Plot {

PlotQChart::PlotQChart(QWidget* parent) : QChartView(parent) {
	SetWidgetRep(this);

	PlotChart = new QChart;
	LogTimeAxisQt = new QLogValueAxis;
	LogQuantityAxisQt = new QLogValueAxis;

	TimeAxisQt = new QValueAxis;
	QuantityAxisQt = new QValueAxis;

	PlotChart->addAxis(TimeAxisQt, Qt::AlignBottom);
	PlotChart->addAxis(LogTimeAxisQt, Qt::AlignBottom);
	SetAxis(Axis::Time, GetAxisInfoView(Axis::Time));

	PlotChart->addAxis(QuantityAxisQt, Qt::AlignLeft);
	PlotChart->addAxis(LogQuantityAxisQt, Qt::AlignLeft);
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
	QLogValueAxis* axlogqt;
	QValueAxis* axqt;

	switch (axis) {
	case Axis::Time:
		axqt = TimeAxisQt;
		axlogqt = LogTimeAxisQt;
		break;
	case Axis::Quantity:
	default:
		axqt = QuantityAxisQt;
		axlogqt = LogQuantityAxisQt;
		break;
	}

	if (!axqt || !axlogqt) { return; };
	axqt->setRange(ax.Range[0], ax.Range[1]);
	axqt->setMinorTickCount(ax.MinorSpacing);

	switch (ax.Scaling) {
	case AxisScaling::Log10:
		axqt->setVisible(false);
		axlogqt->setVisible();

		axlogqt->setBase(10.0);
		break;
	case AxisScaling::Ln:
		axqt->setVisible(false);
		axlogqt->setVisible();

		axlogqt->setBase(2.71828);
		break;
	case AxisScaling::Linear:
	default:
		axlogqt->setVisible(false);
		axqt->setVisible();
		break;
	}

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
