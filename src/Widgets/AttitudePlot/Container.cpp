#include <QHBoxLayout>

#include <vector>
#include <cmath>
#include "Container.h"

namespace VSCL {

AttitudePlotContainer::AttitudePlotContainer(QWidget* parent) : QWidget(parent) {
	QHBoxLayout* boxlay = new QHBoxLayout;
	boxlay->setContentsMargins(5, 5, 5, 5);
	setLayout(boxlay);

	Plot = new AttitudePlot(this);

	QSizePolicy plotSizePolicy;
	plotSizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
	plotSizePolicy.setVerticalPolicy(QSizePolicy::Expanding);
	Plot->setSizePolicy(plotSizePolicy);

	boxlay->addWidget(Plot);

	// TEMP
	for (int i = 0; i < 100; i++) {
		Plot->AddPoint(i, std::cos(i / 12));
	}
};

} // namespace VSCL
