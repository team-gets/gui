
#include "Container.h"

namespace VSCL::Plot {

PlotContainer::PlotContainer(QWidget* parent, EmbeddablePlot2D* newPlot)
	: QWidget(parent) {
	QHBoxLayout* boxlay = new QHBoxLayout;
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

} // namespace VSCL::Plot
