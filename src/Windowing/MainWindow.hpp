#pragma once

#include <QtWidgets>

#include "Widgets/Dial/Composite.hpp"
#include "Widgets/Displays/MultiPlotContainer.hpp"
#include "Util/Sizing.hpp"

namespace VSCL {
class MainWindow : public QMainWindow {

public:
    MainWindow();
	virtual void resizeEvent(QResizeEvent* event) override;
	
private:
	QWidget* MajorContainer;

	QFrame* AttitudeDialRow;
	CompositeDial* RollDial;
	CompositeDial* PitchDial;
	CompositeDial* YawDial;

	MultiPlotContainer* Plots;

	QGroupBox* ActionsRow;
	QPushButton* StandbyIndicator;
	QPushButton* ArmedIndicator;
	QPushButton* InitiateButton;
	QPushButton* AbortButton;
	bool ArmedButtonActive = false;

	QGridLayout* MajorLayout;
	QVBoxLayout* AttitudeDialOrganizer;
	QHBoxLayout* ActionsRowOrganizer;

	QFont ButtonFont{ };
	Util::FontAdjustment ButtonFontAdjustment{ .PxSizeAtMinimum=12 };
	QFont AbortFont{ };
	Util::FontAdjustment AbortFontAdjustment{ .PxSizeAtMinimum=12 };

	void SetupCentralWidget();
	void SetupAttitudeDials();
	void SetupMultiPlot(); 
	void SetupTimeHistoryPlotQChart();
	void SetupActionsRow();
	void SetupButtons();
	void SetAllButtonTextSize();

private slots:
    void About();
	void LoadTestRoutine();
	void OnArmedButtonPressed();

private:
    void CreateActions();
    void CreateMenus();

	QMenu* FileMenu;
    QMenu* EditMenu;
    QMenu* HelpMenu;

    QAction* LoadAct;
    QAction* ExitAct;
    QAction* AboutAct;
}; // class MainWindow }}}
} // namespace VSCL
// vim: foldmethod=marker
