#pragma once

#include <QWidget>
#include "qtgr/grwidget.h"

#include "APIGR.hpp"
#include "Plotting/Plot2D.hpp"
#include "ColorGR.hpp"

namespace VSCL::Plot {

class GR_BACKEND PlotGR : public GRWidget, virtual public EmbeddablePlot2D {

public:
	PlotGR(QWidget* parent);

	virtual void SetAxis(const Axis axis, const AxisInfo& info) override;
	virtual void SetTitle(const std::string& title) override;
	virtual void Plot() override;
	virtual void EraseAllData() override;

protected:
	void UpdateAxes();
	void UpdateSeries();

	virtual void draw() override;

	// Mostly here for interaction with GR C API
	int DoubleVectorToArray(const std::vector<double>& original,
			double* output, const size_t arrSize);

public:
	static uint16_t ColorIndex(ColorGR color) { return static_cast<uint16_t>(color); }
}; // class PlotGR
} // namespace VSCL::Plot
