#include <QHBoxLayout>

#include "Container.h"

namespace VSCL {

AttitudePlotContainer::AttitudePlotContainer(QWidget* parent) : QWidget(parent) {
	QHBoxLayout* boxlay = new QHBoxLayout;
	boxlay->setContentsMargins(5, 5, 5, 5);
	setLayout(boxlay);

	Plot = new AttitudePlot(this);
	boxlay->addWidget(Plot);
};

} // namespace VSCL
