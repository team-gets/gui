#include <iostream>
#include <QHBoxLayout>
#include "Plot2D.hpp"

namespace VSCL::Plot {

void EmbeddablePlot2D::AddPoint(double time, double quantity, bool update) { AddPoint(0, time, quantity, update); }
void EmbeddablePlot2D::AddPoint(uint8_t idx, double time, double quantity, bool update) {
	std::vector<double>& oldTime = Series[idx].Times;
	std::vector<double>& oldQty = Series[idx].Quantities;

	oldTime.push_back(time);
	oldQty.push_back(quantity);
	
	Plot::AxisInfo axInfo = this->GetAxisInfoView(Plot::Axis::Time);
    double maxTime = oldTime.back();
    double minTime = std::max(0.0, maxTime - 10.0);
    axInfo.Range = { minTime, minTime + 10.0 };
    SetAxis(Plot::Axis::Time, axInfo);

	if (update) Plot();
}

void EmbeddablePlot2D::AddPoints(uint8_t idx,
		const std::vector<double>& times, const std::vector<double>& quantities, bool update) {
	std::vector<double>& oldTime = Series[idx].Times;
	std::vector<double>& oldQty = Series[idx].Quantities;

	oldTime.reserve(oldTime.size() + times.size());
	oldQty.reserve(oldQty.size() + quantities.size());

	for (double time : times) {
		oldTime.push_back(time);
	}

	for (double quantity : quantities) {
		oldQty.push_back(quantity);
	}

	if (update) Plot();
}
void EmbeddablePlot2D::AddPoints(
		const std::vector<double>& times, const std::vector<double>& quantities, bool update) {
			AddPoints(0, times, quantities, update); }

void EmbeddablePlot2D::SetAxis(const Axis axis, const AxisInfo& info) {
	switch (axis) {
	case Axis::Time:
		TimeAxis = info;
		break;
	case Axis::Quantity:
		QuantityAxis = info;
		break;
	}
	Plot();
}

void EmbeddablePlot2D::SetTitle(const std::string& title) { Title = title; Plot(); }

void EmbeddablePlot2D::Plot() {
	update();
}

void EmbeddablePlot2D::EraseAllData() {
	for (SeriesInfo& series : Series) {
		series.Times.clear();
		series.Quantities.clear();
	}
	Plot();
}

const AxisInfo& EmbeddablePlot2D::GetAxisInfoView(Axis axis) const {
	switch (axis) {
	case Axis::Time:
		return TimeAxis;
		break;
	case Axis::Quantity:
	default:
		return QuantityAxis;
		break;
	};
}

// Series {{{
void EmbeddablePlot2D::AddSeries() { Series.push_back(SeriesInfo()); Plot(); }
void EmbeddablePlot2D::AddSeries(std::string& name) {
	SeriesInfo serie;
	serie.Name = name;
	Series.push_back(serie);
	Plot();
}
void EmbeddablePlot2D::AddSeries(const SeriesInfo& newInfo) { Series.push_back(newInfo); Plot(); };

SeriesInfo EmbeddablePlot2D::GetSeriesByName(std::string& name) {
	for (const SeriesInfo& serie : Series) {
		if (serie.Name == name) {
			return serie;
		}
	}

	std::cout << "Warning: Series of name " << name << " not found\n";
	return SeriesInfo();
}

const SeriesInfo& EmbeddablePlot2D::GetSeriesViewByName(std::string& name) const {
	for (const SeriesInfo& serie : Series) {
		if (serie.Name == name) {
			return serie;
		}
	}

	std::cout << "Warning: Series of name " << name << " not found. Returning a view of the first series.\n";
	return Series[0];
}

void EmbeddablePlot2D::SetSeries(std::string& name, SeriesInfo& newInfo) {
	for (SeriesInfo& serie : Series) {
		if (serie.Name == name) {
			serie = newInfo;
			return;
		}
	}

	std::cout << "Warning: Series of name " << name << " not found. Doing nothing.\n";
}

void EmbeddablePlot2D::SetSeries(uint8_t idx, SeriesInfo& newInfo) { Series[idx] = newInfo; }

void EmbeddablePlot2D::RemoveSeries(uint8_t idx) { Series.erase(Series.begin() + idx); }
void EmbeddablePlot2D::RemoveSeries(std::string& name) {
	uint8_t n = 0;
	for (const SeriesInfo& serie : Series) {
		if (serie.Name == name) {
			Series.erase(Series.begin() + n);
			Plot();
			return;
		}

		n++;
	}

	std::cout << "Warning: Series of name " << name << " not found. Nothing was removed.\n";
	Plot();
}

const std::vector<SeriesInfo>& EmbeddablePlot2D::GetSeriesInfosView() const { return Series; }

std::vector<double> EmbeddablePlot2D::GetTimes(uint8_t idx) const { return Series[idx].Times; }
std::vector<double> EmbeddablePlot2D::GetTimes() const { return GetTimes(0); }
std::vector<double> EmbeddablePlot2D::GetQuantities(uint8_t idx) const { return Series[idx].Quantities; }
std::vector<double> EmbeddablePlot2D::GetQuantities() const { return GetQuantities(0); }

void EmbeddablePlot2D::SetColor(uint8_t idx, ColorRGB& color) { Series[idx].Color = color; Plot(); }
void EmbeddablePlot2D::SetColor(ColorRGB& color) { SetColor(0, color); Plot(); }
// }}}
} // namespace VSCL::Plot
// vim: foldmethod=marker
