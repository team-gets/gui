#pragma once

#include <QWidget>

#include <array>
#include <string>
#include <vector>

#include "Axes.h"

namespace VSCL::Plot {

// Plotting interface.
// The embeddable plot has at most, one figure inside of it.
// Should probably look at typical plotting implementations for scientific programming
class EmbeddablePlot {
public:
	void AddPoint(const double time, const double quantity);
	void AddPoints(const std::vector<double>& times, const std::vector<double>& quantities);

	// Set axis properites based on the struct
	virtual void SetAxis(Axis axis, AxisInfo& info) { };

	// Set the main title
	virtual void SetTitle(const std::string& title) { };

	// This is called after all the setup and is a call to (re)draw.
	virtual void Plot();

	// Clear data that was being stored.
	virtual void EraseAllData();

	std::vector<double> GetTimes() const;
	std::vector<double> GetQuantities() const;
	QWidget* GetWidgetRep() const;
	void SetWidgetRep(QWidget* newWidgetRep);

private:
	std::vector<double> Times;
	std::vector<double> Quantities;

	// The underlying widget.
	// This is potentially going to lead to an obtuse interface when programming?
	QWidget* WidgetRep;

}; // class AttitudePlot
} // namespace VSCL::Plot
