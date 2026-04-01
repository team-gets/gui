
#include "Container.hpp"

namespace VSCL::Plot {

PlotContainer::PlotContainer(QWidget* parent, EmbeddablePlot2D* newPlot)
	: QWidget(parent) {
	QHBoxLayout* boxlay = new QHBoxLayout(this);
	boxlay->setContentsMargins(5, 5, 5, 5);
	setLayout(boxlay);

	Plot = newPlot;
	Plot->GetWidgetRep()->setParent(this);

	QSizePolicy plotSizePolicy;
	plotSizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
	plotSizePolicy.setVerticalPolicy(QSizePolicy::Expanding);
	Plot->GetWidgetRep()->setSizePolicy(plotSizePolicy);

	boxlay->addWidget(Plot->GetWidgetRep());

	Plot->Plot();
}
EmbeddablePlot2D* PlotContainer::GetPlot() const { return Plot; }
} // namespace VSCL::Plot
