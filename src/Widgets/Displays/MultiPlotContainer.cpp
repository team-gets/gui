#include <cassert>

#include "MultiPlotContainer.hpp"
#include "Plotting/Backend/CoreQChart.hpp"

namespace VSCL {
MultiPlotContainer::MultiPlotContainer(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* Organizers = new QVBoxLayout(this);
    Organizers->setContentsMargins(5, 5, 5, 5);
    // Organizers->setSpacing(0);
    setLayout(Organizers); 
}

MultiPlotContainer::MultiPlotContainer(QWidget* parent, int n) : MultiPlotContainer(parent) {
   for (int i = 0; i < n; i++) {
        Plot::EmbeddablePlot2D* plot = static_cast<Plot::EmbeddablePlot2D*>(new Plot::PlotQChart(this));
        plot->AddSeries();

        Plots.append(plot);
        layout()->addWidget(plot);
        plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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
} // namespace VSCL