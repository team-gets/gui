#include <QHBoxLayout>

#include <cmath>

#include "PlotGR.h"
#include "Container.h"

namespace VSCL::Plot {

PlotContainer::PlotContainer(QWidget* parent) : QWidget(parent) {
	QHBoxLayout* boxlay = new QHBoxLayout;
	boxlay->setContentsMargins(5, 5, 5, 5);
	setLayout(boxlay);

	Plot = new Plot::PlotGR(this);

	QSizePolicy plotSizePolicy;
	plotSizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
	plotSizePolicy.setVerticalPolicy(QSizePolicy::Expanding);
	Plot->GetWidgetRep()->setSizePolicy(plotSizePolicy);

	boxlay->addWidget(Plot->GetWidgetRep());

	// TEMP
	for (int i = 0; i < 100; i++) {
		Plot->AddPoint(i, std::cos(i / 12));
	}
};

} // namespace VSCL::Plot
