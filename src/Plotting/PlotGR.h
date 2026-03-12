#pragma once

#include <QWidget>

#include "Plot.h"
#include "qtgr/grwidget.h"

namespace VSCL::Plot {

class PlotContainer;

class PlotGR : public EmbeddablePlot, public GRWidget {

	friend class PlotContainer;
public:
	PlotGR(QWidget* parent);

protected:
	virtual void draw() override;

	// Mostly here for interaction with GR C API
	int DoubleVectorToArray(const std::vector<double>& original,
			double* output, const size_t arrSize);

};
} // namespace VSCL::Plot
