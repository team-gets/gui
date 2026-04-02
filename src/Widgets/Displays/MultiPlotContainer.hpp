#pragma once 

#include <QWidget>
#include "Plotting/Plot2D.hpp"

namespace VSCL {
class MultiPlotContainer : public QWidget {

    Q_OBJECT;

public:
    MultiPlotContainer(QWidget* parent);
    MultiPlotContainer(QWidget* parent, int n);
    virtual void resizeEvent(QResizeEvent *event) override;

    QList<Plot::EmbeddablePlot2D*> GetPlots() const;
    const QList<Plot::EmbeddablePlot2D*>& GetPlotsView() const;

private:
    QList<Plot::EmbeddablePlot2D*> Plots;
    int NumberOfPlots;

}; // class MultiPlotContainer
} // namespace VSCL
