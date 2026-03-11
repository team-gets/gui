#pragma once

#include <QWidget>
#include "qtgr/grwidget.h"

namespace VSCL {
class AttitudePlot : public GRWidget {

	Q_OBJECT;

public:
	AttitudePlot(QWidget* parent);

	void AddPoint(const double time, const double angle);

protected:
	virtual void draw();

	// Mostly here for interaction with GR C API
	int DoubleVectorToArray(const std::vector<double>& original,
			double* output, const size_t arrSize);
	
private:
	std::vector<double> Times;
	std::vector<double> Angles;

}; // class AttitudePlot
} // namespace VSCL
