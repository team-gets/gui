#pragma once

#include <array>

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QStackedWidget>

#include <QWidget>
#include <QLayout>
#include <QQuickWidget>

#include <QActionGroup>

#include "Widgets/Dial/AttitudeDial.h"
#include "Plotting/Container.h"

namespace VSCL::FromPpt {
class Widgets : public QMainWindow {

public:
    Widgets();

protected:

private:
	QWidget* MajorContainer;
	QWidget* AttitudeDialRow;
	std::array<AttitudeDial*, 3> Dials;
	Plot::PlotContainer* TimeHistory;
	QWidget* StatusColumn;

// Menubar and Actions {{{
private slots:
    void About();

private:
    void CreateActions();
    void CreateMenus();

	QMenu* FileMenu;
    QMenu* EditMenu;
    QMenu* HelpMenu;

    QAction* ExitAct;
    QAction* AboutAct;
// }}}
}; // class Widgets
} // namespace VSCL::FromPpt
// vim: foldmethod=marker
