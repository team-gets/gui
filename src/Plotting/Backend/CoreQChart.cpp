#include "CoreQChart.h"

namespace VSCL {

PlotQChart::PlotQChart(QWidget* parent) : QChartView(parent) {
	SetWidgetRep(this);
};

} // namespace VSCL
