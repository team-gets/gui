#pragma once

#include <QtWidgets>

#include "Widgets/Dial/Composite.hpp"
#include "Plotting/Plot2D.hpp"
#include "Util/Sizing.hpp"
#include "Widgets/Displays/MultiPlotContainer.hpp"

namespace VSCL {
class MainWindow : public QMainWindow {

public:
    MainWindow();
	virtual void resizeEvent(QResizeEvent* event) override;
	
private:
	QFont ButtonFont{ };
	Util::FontAdjustment ButtonFontAdjustment{ .PxSizeAtMinimum=12 };
	QFont AbortFont{ };
	Util::FontAdjustment AbortFontAdjustment{ .PxSizeAtMinimum=12 };

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

	void SetupCentralWidget();
	void SetGridColumnsMinimums();
	void SetGridRowsMinimums();
	void SetupAttitudeDials();
	void SetupMultiPlot(); 
	void SetupTimeHistoryPlotQChart();
	void SetupButtons();
	void SetupActionsRow();
	void SetAllButtonTextSize();

private slots:
    void About();
	void OnArmedButtonPressed();

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
} // namespace VSCL
// vim: foldmethod=marker
