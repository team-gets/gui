#pragma once

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

#include "Plotting/Container.h"

namespace VSCL::FromPpt {
class Widgets : public QMainWindow {

public:
    Widgets();

protected:

private slots:
    void About();

private:
	Plot::PlotContainer* PlotContainer;

	/*
	 *	Actions
	 */

    void CreateActions();
    void CreateMenus();

	QMenu* FileMenu;
    QMenu* EditMenu;
    QMenu* HelpMenu;

    QAction* ExitAct;
    QAction* AboutAct;
}; // class Widgets
} // namespace VSCL::FromPpt
