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
	boxlay->addWidget(Plot);

	// TEMP
	for (int i = 0; i < 100; i++) {
		Plot->AddPoint(i, std::sin(3.14 * i / 12));
	}
};

} // namespace VSCL
