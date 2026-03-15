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

	Plot::EmbeddablePlot2D* Plot;
	Plot::PlotContainer* TimeHistory;
	void SetupTimeHistoryPlot();

	// im not entirely sure of this part
	QGroupBox* StatusColumn;
	QVBoxLayout* StatusColumnOrganizer;
	QPushButton* LoadTestRoutineButton;
	QPushButton* QuantityCalculatorButton;
	QPushButton* LogOpenButton;
	QPushButton* AbortButton;
	void SetupButtons();
	void SetupStatusColumn();

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
