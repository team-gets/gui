#pragma once

#include <QChartView>
#include "Plotting/Plot2D.h"
#include "APIQChart.h"

namespace VSCL {

class PlotContainer;

class QCHART_BACKEND PlotQChart : public Plot::EmbeddablePlot2D, public QChartView  {

	friend class PlotContainer;

public:
	PlotQChart(QWidget* parent);

private:
	QChart* Plot;

}; // class PlotQChart
} // namespace VSCL
