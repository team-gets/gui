#pragma once

#include <QWidget>

#include "Plot.h"
#include "grwidget.h"

namespace VSCL::Plot {
class PlotGR : public EmbeddablePlot, public GRWidget {

public:
	PlotGR(QWidget* parent);

protected:
	virtual void draw();

	// Mostly here for interaction with GR C API
	int DoubleVectorToArray(const std::vector<double>& original,
			double* output, const size_t arrSize);

};
} // namespace VSCL::Plot
