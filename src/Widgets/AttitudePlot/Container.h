#pragma once

#include <QtWidgets>
#include "Plot.h"

namespace VSCL {
class AttitudePlotContainer : public QWidget {

	Q_OBJECT;

public:
	AttitudePlotContainer(QWidget* parent);

private:
	AttitudePlot* Plot;

}; // class AttitudePlotContainer
} // namespace VSCL
