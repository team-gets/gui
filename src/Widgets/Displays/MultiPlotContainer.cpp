#include <cassert>
#include <array>

#include "MultiPlotContainer.hpp"
#include "Plotting/Backend/CoreGR.hpp"
#include "Plotting/Backend/CoreQChart.hpp"

namespace VSCL {
MultiPlotContainer::MultiPlotContainer(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* Organizers = new QVBoxLayout(this);
    setLayout(Organizers); 
}
MultiPlotContainer::MultiPlotContainer(QWidget* parent, int n) : MultiPlotContainer(parent) {
   for (int i = 0; i < n; i++) {
        Plot::PlotQChart *plot = new Plot::PlotQChart(this);
        plot->AddSeries();
        Plot::PlotContainer *container = new Plot::PlotContainer(this, plot);
        Plots.append(container);
        layout()->addWidget(container);
   }
   numberOfPlots = n;
   AddPoints(2);
}
void MultiPlotContainer::resizeEvent(QResizeEvent* event) { }
QList<Plot::PlotContainer*> MultiPlotContainer::GetPlotContainers() const {
    return Plots;
}
const QList<Plot::PlotContainer*>& MultiPlotContainer::GetPlotContainersView() const {
    return Plots;
}
void MultiPlotContainer::AddPoints(int n) {
    if (n < 0 || n >= numberOfPlots || Plots.isEmpty()) return;
    Plot::PlotContainer* plotContainer = Plots.last();
    Plot::EmbeddablePlot2D* plot = plotContainer->GetPlot();
    plot->AddPoint(0, -1, 0.5);
    plot->Plot();
}
}
