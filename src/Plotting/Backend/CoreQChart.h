#pragma once

#include <QtCharts>
#include "Plotting/Plot2D.h"
#include "Plotting/Axes.h"
#include "APIQChart.h"

namespace VSCL::Plot {

class PlotContainer;

class QCHART_BACKEND PlotQChart : public EmbeddablePlot2D, public QChartView  {

	friend class PlotContainer;

public:
	PlotQChart(QWidget* parent);
	virtual ~PlotQChart();

	virtual void SetAxis(const Axis axis, const AxisInfo& info) override;
	virtual void SetTitle(const std::string& title) override;
	virtual void Plot() override;
	virtual void EraseAllData() override;

	virtual void AddSeries(const SeriesInfo& newInfo) override;

private:
	QChart* PlotChart;
	QValueAxis* TimeAxisQt;
	QValueAxis* QuantityAxisQt;

}; // class PlotQChart
} // namespace VSCL::Plot
