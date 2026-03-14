#pragma once

#include <array>
#include <QtWidgets>

#include "Widgets/Dial/AttitudeDial.h"
#include "Plotting/Container.h"

namespace VSCL::FromPpt {
class Widgets : public QMainWindow {

public:
    Widgets();

private:
	QWidget* MajorContainer;
	QGridLayout* MajorLayout;
	void SetupCentralWidget();

	QFrame* AttitudeDialRow;
	QHBoxLayout* AttitudeDialOrganizer;

	AttitudeDial* RollDial;
	AttitudeDial* PitchDial;
	AttitudeDial* YawDial;
	std::array<AttitudeDial*, 3> Dials;
	void SetupAttitudeDials();

	Plot::PlotContainer* TimeHistory;
	QFrame* StatusColumn;

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
