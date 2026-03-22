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
	~PlotQChart();

	virtual void SetAxis(Axis axis, AxisInfo& info) override;
	virtual void SetTitle(const std::string& title) override;
	virtual void Plot() override;
	virtual void EraseAllData() override;

private:
	QChart* PlotChart;
	QList<QLineSeries*> QLineSerieses;
	QValueAxis* QTimeAxis;
	QValueAxis* QQuantityAxis;

}; // class PlotQChart
} // namespace VSCL::Plot
