#pragma once

#include <QWidget>

#include <string>
#include <vector>
#include <cstdint>

#include "Axes.h"
#include "Series.h"

namespace VSCL::Plot {

// 2D plotting interface.
// The embeddable plot has at most, one figure inside of it. A figure will have multiple serieses.
//
// TODO: probably look at typical plotting implementations for scientific programming
class EmbeddablePlot2D {
public:
	void AddPoint(uint8_t idx, double time, double quantity);
	void AddPoint(double time, double quantity);
	void AddPoints(uint8_t idx, const std::vector<double>& times, const std::vector<double>& quantities);
	void AddPoints(const std::vector<double>& times, const std::vector<double>& quantities);

	// Set axis properites based on the struct
	virtual void SetAxis(Axis axis, AxisInfo& info);

	// Set the main title
	virtual void SetTitle(const std::string& title);

	// This is called after all the setup and is a call to (re)draw.
	virtual void Plot();

	// Clear data that was being stored.
	virtual void EraseAllData();

	std::vector<double> GetTimes(uint8_t idx) const;
	std::vector<double> GetTimes() const;
	std::vector<double> GetQuantities(uint8_t idx) const;
	std::vector<double> GetQuantities() const;
	QWidget* GetWidgetRep() const;
	void SetWidgetRep(QWidget* newWidgetRep);

private:	
	std::string Title;
	AxisInfo TimeAxis = { Axis::Time };
	AxisInfo QuantityAxis = { Axis::Quantity };

	std::vector<SeriesInfo> Series = { SeriesInfo { } };

	// The underlying widget.
	// This is potentially going to lead to an obtuse interface when programming?
	QWidget* WidgetRep;

}; // class AttitudePlot
} // namespace VSCL::Plot
