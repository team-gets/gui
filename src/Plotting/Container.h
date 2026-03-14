#pragma once

#include <QtWidgets>
#include <QHBoxLayout>

#include "Plot2D.h"

namespace VSCL::Plot {

// The intent is to put stuff next to the embedded plot
class PlotContainer : public QWidget {

	Q_OBJECT;

public:
	PlotContainer(QWidget* parent, EmbeddablePlot2D* newPlot);

private:
	EmbeddablePlot2D* Plot;

}; // class AttitudePlotContainer
} // namespace VSCL::Plot
