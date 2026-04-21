#pragma once

#include <array>
#include <QtWidgets>

#include "Widgets/Dial/Composite.hpp"
#include "Widgets/Displays/QuantitiesRatesDisplay.hpp"
#include "Widgets/Displays/QuantitiesRatesRow.hpp"
#include "Plotting/Plot2D.hpp"
#include "Util/Sizing.hpp"
#include "Widgets/Displays/MultiPlotContainer.hpp"

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
	QFont ButtonFont{ };
	Util::FontAdjustment ButtonFontAdjustment{ .PxSizeAtMinimum=12 };
	QFont AbortFont{ };
	Util::FontAdjustment AbortFontAdjustment{ .PxSizeAtMinimum=12 };

	QWidget* MajorContainer;
	QGridLayout* MajorLayout;
	void SetupCentralWidget();
	void SetGridColumnsMinimums();
	void SetGridRowsMinimums();

	QFrame* AttitudeDialRow;
	QVBoxLayout* AttitudeDialOrganizer;

	CompositeDial* RollDial;
	CompositeDial* PitchDial;
	CompositeDial* YawDial;
	std::array<CompositeDial*, 3> Dials;
	void SetupAttitudeDials();

	Plot::EmbeddablePlot2D* Plot;
	MultiPlotContainer* Plots;
	void SetupMultiPlot(); 

	void SetupTimeHistoryPlotQChart();

	QtyRateDisplay* AttQtysRates;
	QtyRateRow* RollQtyRate;
	QtyRateRow* PitchQtyRate;
	QtyRateRow* YawQtyRate;
	void SetupAttQtysRatesDisplay();

	// im not entirely sure of this part
	QGroupBox* StatusColumn;
	QHBoxLayout* StatusColumnOrganizer;
	QPushButton* StandbyIndicator;
	QPushButton* ArmedIndicator;
	QPushButton* InitiateButton;
	QPushButton* LogOpenButton;
	QPushButton* AbortButton;
	bool ArmedButtonActive = false;  // Track armed button state

	void SetupButtons();
	void SetupStatusColumn();
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
} // namespace VSCL::FromPpt
// vim: foldmethod=marker
