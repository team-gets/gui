#include <QHBoxLayout>
#include "Plot.h"

namespace VSCL::Plot {

void EmbeddablePlot::AddPoint(const double time, const double angle) {
	Times.push_back(time);
	Angles.push_back(angle);

	if (WidgetRep)
		WidgetRep->update();
}

std::vector<double> EmbeddablePlot::GetTimes() const { return Times; }
std::vector<double> EmbeddablePlot::GetAngles() const { return Angles; }
QWidget* EmbeddablePlot::GetWidgetRep() const { return WidgetRep; }
void EmbeddablePlot::SetWidgetRep(QWidget* newWidgetRep) { WidgetRep = newWidgetRep; }

} // namespace VSCL::Plot
