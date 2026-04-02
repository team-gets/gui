#include <iostream>
#include "CoreQChart.hpp"

namespace VSCL::Plot {

PlotQChart::PlotQChart(QWidget* parent)
	: QChartView(parent) {

	// These heap allocs are parented and handled when they get added to each other
	PlotChart = new QChart;

	LogTimeAxisQt = new QLogValueAxis;
	LogQuantityAxisQt = new QLogValueAxis;
	TimeAxisQt = new QValueAxis;
	QuantityAxisQt = new QValueAxis;

	PlotChart->addAxis(TimeAxisQt, Qt::AlignBottom);
	TimeAxisQt->setLinePenColor(QColorConstants::Black);
	// TimeAxisQt->setLabelFormat("%i");

	PlotChart->addAxis(LogTimeAxisQt, Qt::AlignBottom);
	LogTimeAxisQt->setLinePenColor(QColorConstants::Black);
	// LogTimeAxisQt->setLabelFormat("%g");
	LogTimeAxisQt->setGridLineVisible(false);
	SetAxis(Axis::Time, GetAxisInfoView(Axis::Time));

	PlotChart->addAxis(QuantityAxisQt, Qt::AlignLeft);
	QuantityAxisQt->setLinePenColor(QColorConstants::Black);
	// QuantityAxisQt->setLabelFormat("%i");

	PlotChart->addAxis(LogQuantityAxisQt, Qt::AlignLeft);
	LogQuantityAxisQt->setLinePenColor(QColorConstants::Black);
	// LogQuantityAxisQt->setLabelFormat("%g");
	LogQuantityAxisQt->setGridLineVisible(false);
	SetAxis(Axis::Quantity, GetAxisInfoView(Axis::Quantity));

	PlotChart->legend()->setVisible(false);
	PlotChart->setTheme(QChart::ChartThemeLight);
	setChart(PlotChart);
	setRenderHint(QPainter::RenderHint::Antialiasing);
}

PlotQChart::~PlotQChart() {
	if (PlotChart)
		delete PlotChart;
}

void PlotQChart::SetAxis(const Axis axis, const AxisInfo& info) {
	EmbeddablePlot2D::SetAxis(axis, info);
	const AxisInfo& ax = GetAxisInfoView(axis);

	QLogValueAxis* axlogqt;
	QValueAxis* axlinqt;
	QAbstractAxis* axqt;
	double lobd = ax.Range[0];

	switch (axis) {
	case Axis::Time:
		axlinqt = TimeAxisQt;
		axlogqt = LogTimeAxisQt;
		break;
	case Axis::Quantity:
	default:
		axlinqt = QuantityAxisQt;
		axlogqt = LogQuantityAxisQt;
		break;
	}

	if (!axlinqt || !axlogqt) { return; };

	switch (ax.Scaling) {
	case AxisScaling::Log10:
		axlinqt->setVisible(false);
		axlogqt->setVisible();

		axlogqt->setBase(10.0);
		axlogqt->setMinorTickCount(10);
		lobd = (std::abs(lobd) < 1e-15) ? std::numeric_limits<qreal>::epsilon() : lobd ;
		axqt = axlogqt;
		break;

	case AxisScaling::Ln:
		axlinqt->setVisible(false);
		axlogqt->setVisible();

		axlogqt->setBase(2.71828);
		axlogqt->setMinorTickCount(0);
		lobd = (std::abs(lobd) < 1e-15) ? std::numeric_limits<qreal>::epsilon() : lobd ;
		axqt = axlogqt;
		break;

	case AxisScaling::Linear:
	default:
		axlogqt->setVisible(false);
		axlinqt->setVisible();

		axlinqt->setMinorTickCount(ax.MajorSpacing / ax.MinorSpacing);
		axlinqt->setTickCount(std::floor(ax.Range[1] - ax.Range[0]) / ax.MajorSpacing + 1);
		axqt = axlinqt;
		break;
	}

	axlinqt->setRange(lobd, ax.Range[1]);
	axqt->setTitleText(QString::fromStdString(ax.Title));
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
		std::size_t n = sinfo.Times.size();
		if (n == 0) { continue; }

		for (unsigned int i = 0; static_cast<std::size_t>(i) < n; i++) {
			pts.append({ sinfo.Times[i], sinfo.Quantities[i] });
		}

		const ColorRGB& color = sinfo.Color;
		serie->setColor(QColor::fromRgbF(color[0], color[1], color[2], 1.0));

		switch (sinfo.Style) {
		case LineStyle::Dashed:
			std::cerr << "Dashed lines not implemented for Qt Charts.\n";
			break;
		case LineStyle::Dotted:
			std::cerr << "Dotted lines not implemented for Qt Charts.\n";
			break;
		case LineStyle::Solid:
		default:
			break;
		}

		serie->setName(QString::fromStdString(sinfo.Name));
		serie->replace(pts);
		idx++;
	}
}

void PlotQChart::EraseAllData() {
	EmbeddablePlot2D::EraseAllData();
}

void PlotQChart::AddSeries() {
	AddSeries({ });
}

void PlotQChart::AddSeries(const SeriesInfo& newInfo) {
	EmbeddablePlot2D::AddSeries(newInfo);

	QLineSeries* newSeries = new QLineSeries(PlotChart);
	PlotChart->addSeries(newSeries);

	newSeries->attachAxis(TimeAxisQt);
	newSeries->attachAxis(LogTimeAxisQt);
	newSeries->attachAxis(QuantityAxisQt);
	newSeries->attachAxis(LogQuantityAxisQt);

	Plot();
}
} // namespace VSCL::Plot
