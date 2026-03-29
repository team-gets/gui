#pragma once

#include <array>
#include <QtWidgets>

#include "Widgets/Dial/Attitude.hpp"
#include "Widgets/Displays/QuantitiesRatesDisplay.hpp"
#include "Widgets/Displays/QuantitiesRatesRow.hpp"
#include "Plotting/Container.hpp"
#include "Util/Sizing.hpp"

namespace VSCL::FromPpt {
class Widgets : public QMainWindow {

public:
    Widgets();
	virtual void resizeEvent(QResizeEvent* event) override;
	
	void SetRoll(double roll);
	void SetPitch(double pitch);
	void SetYaw(double yaw);
	void SetRollRate(double roll);
	void SetPitchRate(double pitch);
	void SetYawRate(double yaw);

private:
	QFont ButtonFont;

	QWidget* MajorContainer;
	QGridLayout* MajorLayout;
	void SetupCentralWidget();
	void SetGridColumnsMinimums();
	void SetGridRowsMinimums();

	QFrame* AttitudeDialRow;
	QHBoxLayout* AttitudeDialOrganizer;

	AttitudeDial* RollDial;
	AttitudeDial* PitchDial;
	AttitudeDial* YawDial;
	std::array<AttitudeDial*, 3> Dials;
	void SetupAttitudeDials();

	Plot::EmbeddablePlot2D* Plot;
	Plot::PlotContainer* TimeHistory;
	void SetupTimeHistoryPlotGR();
	void SetupTimeHistoryPlotQChart();

	QtyRateDisplay* AttQtysRates;
	QtyRateRow* RollQtyRate;
	QtyRateRow* PitchQtyRate;
	QtyRateRow* YawQtyRate;
	void SetupAttQtysRatesDisplay();

	// im not entirely sure of this part
	QGroupBox* StatusColumn;
	QVBoxLayout* StatusColumnOrganizer;
	QPushButton* LoadTestRoutineButton;
	QPushButton* QuantityCalculatorButton;
	QPushButton* LogOpenButton;
	QPushButton* AbortButton;
	Util::FontAdjustment ButtonFontAdjustment{ 12 };
	void SetupButtons();
	void SetupStatusColumn();
	void SetAllButtonTextSize();

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
