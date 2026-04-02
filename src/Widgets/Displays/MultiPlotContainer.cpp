#include <cassert>

#include "MultiPlotContainer.hpp"
#include "Plotting/Backend/CoreQChart.hpp"

namespace VSCL {
MultiPlotContainer::MultiPlotContainer(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* Organizers = new QVBoxLayout(this);
    Organizers->setContentsMargins(0, 0, 0, 0);
    Organizers->setSpacing(0);
    setLayout(Organizers); 
}
MultiPlotContainer::MultiPlotContainer(QWidget* parent, int n) : MultiPlotContainer(parent) {
   for (int i = 0; i < n; i++) {
        Plot::PlotQChart *plot = new Plot::PlotQChart(this);
        plot->AddSeries();
        Plots.append(plot);
        layout()->addWidget(static_cast<Plot::EmbeddablePlot2D*>(plot));
        // plot->GetWidgetRep()->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
   }
   NumberOfPlots = n;
}
void MultiPlotContainer::resizeEvent(QResizeEvent* event) { }
QList<Plot::EmbeddablePlot2D*> MultiPlotContainer::GetPlots() const {
    return Plots;
}
const QList<Plot::EmbeddablePlot2D*>& MultiPlotContainer::GetPlotsView() const {
    return Plots;
}
void MultiPlotContainer::AddPoints(int n) {
    if (n < 0 || n >= NumberOfPlots || Plots.isEmpty()) return;
    Plot::EmbeddablePlot2D* plot = Plots.last();
    plot->AddPoint(0, -1, 0.5);
    plot->AddPoint(5, 90);
    plot->AddPoint(11, 90);
    plot->Plot();
}
} // namespace VSCL
