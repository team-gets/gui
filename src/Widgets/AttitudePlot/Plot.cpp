#include <QHBoxLayout>

#include <cmath>

#include "gr.h"
#include "Plot.h"

namespace VSCL {

AttitudePlot::AttitudePlot(QWidget* parent) : GRWidget(parent) { }

void AttitudePlot::AddPoint(const double time, const double angle) {
	Times.push_back(time);
	Angles.push_back(angle);
}

int AttitudePlot::DoubleVectorToArray(const std::vector<double>& original,
		double* output, const size_t arrSize) {

	const size_t vecSize = original.size();
	const bool oversized = vecSize > arrSize;

	int stepSize = 1;
	int endDelta = (!oversized) ? 0 : -1;

	// Must take samplings if it's too big to fit
	if (oversized) {
		stepSize = static_cast<int>(std::floor(vecSize / arrSize));
	}

	for (int i = 0; i < arrSize + endDelta; i += stepSize) {
		output[i] = original[i];
	}

	return 0;
}

void AttitudePlot::draw() {
	// Magic number 512 (arbitrary power of 2)
	const size_t vecSize = Times.size();
	const int n = (vecSize < 512) ? vecSize : 512;

	double times[512] = { 0.0 };
	double angls[512] = { 0.0 };

	DoubleVectorToArray(Times, times, 512);
	DoubleVectorToArray(Angles, angls, 512);

	gr_polyline(n, times, angls);
}

} // namespace VSCL
