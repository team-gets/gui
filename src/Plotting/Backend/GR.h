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

public:

	// Reference gr.h 104-123
	// The polyline coloring function takes an int < 1024
	enum class ColorGR : uint16_t {
		Red =		236,
		Green = 	237,
		Yellow =	238,
		Blue =		239,
		Orange =	240,
		Purple =	241,
		Cyan =		242,
		Magenta =	243,
		Lime =		244,
		Pink =		245,
		Teal =		246,
		Lavender =	247,
		Brown =		248,
		Beige =		249,
		Maroon =	250,
		Mint =		251,
		Olive =		252,
		Apricot =	253,
		Navy =		254,
		Grey =		255
	};
};

} // namespace VSCL::Plot
