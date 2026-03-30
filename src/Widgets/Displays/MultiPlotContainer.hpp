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

private:
    QList<Plot::PlotContainer*> Plots;

}; // class MultiPlotContainer
} // namespace VSCL