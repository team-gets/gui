#pragma once

#include <QtWidgets>
#include <QHBoxLayout>

#include "Plot2D.h"

namespace VSCL::Plot {

// The intent is to put stuff next to the embedded plot
class PlotContainer : public QWidget {

	Q_OBJECT;

public:
	PlotContainer(QWidget* parent, EmbeddablePlot2D* newPlot) {
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

		// TEMP
		for (int i = 0; i < 100; i++) {
			//Plot->AddPoint(i, std::cos(i / 12));
			Plot->AddPoint(i / 100.0, std::cos(0.1 * i) / 2.0 + 0.5);
		}

		Plot->Plot();
	};

private:
	EmbeddablePlot2D* Plot;

}; // class AttitudePlotContainer
} // namespace VSCL::Plot
