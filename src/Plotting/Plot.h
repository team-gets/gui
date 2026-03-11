#pragma once

#include <QWidget>
#include <vector>

namespace VSCL::Plot {

// Plotting interface
class EmbeddablePlot {
public:
	void AddPoint(const double time, const double angle);

	std::vector<double> GetTimes() const;
	std::vector<double> GetAngles() const;
	QWidget* GetWidgetRep() const;
	void SetWidgetRep(QWidget* newWidgetRep);

private:
	std::vector<double> Times;
	std::vector<double> Angles;

	// The underlying widget.
	// This is potentially going to lead to an obtuse interface when programming?
	QWidget* WidgetRep;

}; // class AttitudePlot
} // namespace VSCL::Plot
