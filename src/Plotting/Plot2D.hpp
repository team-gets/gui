#pragma once

#include <QWidget>

#include <string>
#include <vector>
#include <cstdint>

#include "PlotAPI.hpp"
#include "Axes.hpp"
#include "Series.hpp"

namespace VSCL::Plot {

// 2D plotting interface.
// The embeddable plot has at most, one figure inside of it.
// A figure can have multiple series.
class PLOT_API EmbeddablePlot2D : virtual public QWidget {
public:
	EmbeddablePlot2D(QWidget* parent);

	void AddPoint(uint8_t idx, double time, double quantity, bool update = false);
	void AddPoint(double time, double quantity, bool update = false);
	void AddPoints(uint8_t idx, const std::vector<double>& times, const std::vector<double>& quantities, bool update = false);
	void AddPoints(const std::vector<double>& times, const std::vector<double>& quantities, bool update = false);

	// Set axis properites based on the struct
	virtual void SetAxis(const Axis axis, const AxisInfo& info);

	// Set the main title
	virtual void SetTitle(const std::string& title);

	// This is called after all the setup and is a call to (re)draw.
	virtual void Plot();

	// Clear data that was being stored.
	virtual void EraseAllData();

	const AxisInfo& GetAxisInfoView(Axis axis) const;

	/*
	 *	Series data.
	 */

	// Add a blank series.
	virtual void AddSeries();
	// Add a named series.
	void AddSeries(std::string& name);
	// Add a series using the following info.
	virtual void AddSeries(const SeriesInfo& newInfo);

	SeriesInfo GetSeriesByName(std::string& name);
	const SeriesInfo& GetSeriesViewByName(std::string& name) const;

	void SetSeries(std::string& name, SeriesInfo& newInfo);
	void SetSeries(uint8_t idx, SeriesInfo& newInfo);

	// Remove the series at the given index.
	void RemoveSeries(uint8_t idx);
	// Remove the named series.
	void RemoveSeries(std::string& name);

	// Get a view of all series info. This is a const reference to the series data.
	const std::vector<SeriesInfo>& GetSeriesInfosView() const;

	// Get the stored time data from the series at index idx.
	std::vector<double> GetTimes(uint8_t idx) const;
	std::vector<double> GetTimes() const;

	// Get the stored quantity data from the series at index idx.
	std::vector<double> GetQuantities(uint8_t idx) const;
	std::vector<double> GetQuantities() const;

	// Set color
	virtual void SetColor(uint8_t idx, ColorRGB& color);
	virtual void SetColor(ColorRGB& color);

	bool GetDrawGridState() { return DrawGrid; };
	void SetDrawGridState(bool newState) { DrawGrid = newState; };

private:	
	std::string Title;
	AxisInfo TimeAxis = { Axis::Time };
	AxisInfo QuantityAxis = { Axis::Quantity };

	std::vector<SeriesInfo> Series;
	bool DrawGrid = false;

	// The underlying widget.
	// This is potentially going to lead to an obtuse interface when programming?
	QWidget* WidgetRep;

}; // class AttitudePlot
} // namespace VSCL::Plot
