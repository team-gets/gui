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
        Plot::PlotContainer *container = new Plot::PlotContainer(this, plot);
        Plots.append(container);
        layout()->addWidget(container);
   }
}
void MultiPlotContainer::resizeEvent(QResizeEvent* event) { }
}