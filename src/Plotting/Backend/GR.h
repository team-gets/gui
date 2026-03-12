#pragma once

#include <QWidget>

#include "Plotting/Plot2D.h"
#include "qtgr/grwidget.h"

namespace VSCL::Plot {

class PlotContainer;

class PlotGR : public EmbeddablePlot2D, public GRWidget {

	friend class PlotContainer;

public:
	PlotGR(QWidget* parent);

	virtual void SetAxis(Axis axis, AxisInfo& info) override;
	virtual void SetTitle(const std::string& title) override;
	virtual void Plot() override;
	virtual void EraseAllData() override;

protected:
	virtual void draw() override;

	// Mostly here for interaction with GR C API
	int DoubleVectorToArray(const std::vector<double>& original,
			double* output, const size_t arrSize);

};
} // namespace VSCL::Plot
