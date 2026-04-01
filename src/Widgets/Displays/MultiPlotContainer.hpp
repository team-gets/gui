#pragma once 

#include <QWidget>
#include "Plotting/Container.hpp"
#include "Util/Sizing.hpp"

namespace VSCL {

class MultiPlotContainer : public QWidget {

    Q_OBJECT;

public:
    MultiPlotContainer(QWidget* parent);
    MultiPlotContainer(QWidget* parent, int n);
    virtual void resizeEvent(QResizeEvent *event) override;

    QList<Plot::PlotContainer*> GetPlotContainers() const;
    const QList<Plot::PlotContainer*>& GetPlotContainersView() const;

    void AddPoints(int n);
private:
    QList<Plot::PlotContainer*> Plots;
    int numberOfPlots;

}; // class MultiPlotContainer
} // namespace VSCL