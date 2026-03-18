#pragma once

#include <QWidget>
#include "qtgr/grwidget.h"

#include "Plotting/Plot2D.h"
#include "ColorGR.h"

class GRWidget;

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
	void UpdateAxes();
	void UpdateSeries();

	virtual void draw() override;

	// Mostly here for interaction with GR C API
	int DoubleVectorToArray(const std::vector<double>& original,
			double* output, const size_t arrSize);

public:
	static constexpr uint16_t ColorIndex(ColorGR color) { return static_cast<uint16_t>(color); }
}; // class PlotGR
} // namespace VSCL::Plot
