#include <cstdlib>
#include <cmath>
#include <chrono>

#include "Windowing/MainWindow.hpp"
#include "Plotting/Backend/CoreQChart.hpp"
#include "Widgets/Displays/StatusCollector.hpp"

// stupid temp thing {{{
static void StupidMakeData(VSCL::Plot::EmbeddablePlot2D* plot) {
	double ph1, ph2, ph3;

	std::srand(std::chrono::system_clock::now().time_since_epoch().count() + 1);
	ph1 = std::rand() % 12;
	std::srand(std::chrono::system_clock::now().time_since_epoch().count() + 3);
	ph2 = std::rand() % 12;
	std::srand(std::chrono::system_clock::now().time_since_epoch().count() + 2);
	ph3 = std::rand() % 12;

	for (int i = 0; i < 100; i++) {
		plot->AddPoint(0, i/10.0, std::cos(0.1 * i + ph1/12) / 2.0 + 0.5);
		plot->AddPoint(1, i/10.0, std::sin(0.1 * i - ph2/12) / 2.0 + 0.5);
		plot->AddPoint(2, i/10.0, std::cos(0.1 * i + ph3/12) / 2.0 + 0.5);
	}

	plot->Plot();
}
// }}}

namespace VSCL {
MainWindow::MainWindow()
	: MajorContainer(new QWidget)

	, AttitudeDialRow(new QFrame(MajorContainer))
	, RollDial(new CompositeDial(AttitudeDialRow))
	, PitchDial(new CompositeDial(AttitudeDialRow))
	, YawDial(new CompositeDial(AttitudeDialRow))

	, ActionsRow(new QGroupBox(tr("Operate"), MajorContainer))
	, StandbyIndicator(new QPushButton(ActionsRow))
	, ArmedIndicator(new QPushButton(ActionsRow))
	, InitiateButton(new QPushButton(ActionsRow))
	, AbortButton(new QPushButton(ActionsRow))

	, MajorLayout(new QGridLayout(this))
	, AttitudeDialOrganizer(new QVBoxLayout(AttitudeDialRow))
	, ActionsRowOrganizer(new QHBoxLayout(ActionsRow))
{
    // Set up menubar and statusbar
    CreateActions();
    CreateMenus();

    QString message = tr("Test Rig Operations");
    statusBar()->showMessage(message);

	// Geometry and window characteristics
    setWindowTitle(tr("VSCL Gyroscopic Test Rig"));
    setMinimumSize(Util::MINIMUM_WIDTH, Util::MINIMUM_HEIGHT);
    resize(Util::MINIMUM_WIDTH, Util::MINIMUM_HEIGHT);

	// Set up the static layout
	SetupCentralWidget();
	SetupAttitudeDials();
	SetupMultiPlot(); // <-new multiplot
	SetupButtons();
	SetupActionsRow();
	SetGridColumnsMinimums();
	SetGridRowsMinimums();

	SetAllButtonTextSize();
} // void MainWindow::Widgets()

void MainWindow::resizeEvent(QResizeEvent* event) {
	QMainWindow::resizeEvent(event);

	SetGridColumnsMinimums();
	SetGridRowsMinimums();
	SetAllButtonTextSize();
} // void MainWindow::resizeEvent()

// Layout and Widgets Setup {{{
void MainWindow::SetupCentralWidget() {
	QSizePolicy majorPolicy;
	majorPolicy.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
	majorPolicy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
	MajorContainer->setSizePolicy(majorPolicy);

	MajorLayout->setContentsMargins(35, 35, 35, 35);
	MajorContainer->setLayout(MajorLayout);

	setCentralWidget(MajorContainer);
} // void MainWindow::SetupCentralWidget()

void MainWindow::SetupAttitudeDials() {
	MajorLayout->addWidget(AttitudeDialRow, 0, 1);

	AttitudeDialOrganizer->setContentsMargins(20, 20, 20, 20);
	AttitudeDialRow->setLayout(AttitudeDialOrganizer);

	QSizePolicy dialsPolicy;
	dialsPolicy.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
	dialsPolicy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
	AttitudeDialRow->setSizePolicy(dialsPolicy);

	AttitudeDialOrganizer->addWidget(RollDial);
	AttitudeDialOrganizer->addWidget(PitchDial);
	AttitudeDialOrganizer->addWidget(YawDial);

	Dials = { RollDial, PitchDial, YawDial };
} // void MainWindow::SetupCentralWidget()

void MainWindow::SetGridColumnsMinimums() {
	if (!MajorLayout) { return; };
	const QRect& dims = centralWidget()->geometry();
	MajorLayout->setColumnMinimumWidth(0,  4 * dims.width() / 5);
	MajorLayout->setColumnMinimumWidth(1, 1 * dims.width() / 5);
} // void MainWindow::SetGridColumnsMinimums()

void MainWindow::SetGridRowsMinimums() {
	if (!MajorLayout) { return; }
	const QRect& dims = centralWidget()->geometry();
	MajorLayout->setRowMinimumHeight(0, 4 * dims.height() / 5);
	MajorLayout->setRowMinimumHeight(1, 1 * dims.height() / 5);
} // void MainWindow::SetGridRowsMinimums()

// Buttons {{{
void MainWindow::SetupButtons() {
	StandbyIndicator->setText(tr("Standby"));
	SetButtonStatus(StandbyIndicator, Status::STANDBY);

	ArmedIndicator->setText(tr("Disarmed"));
	SetButtonStatus(ArmedIndicator, Status::DISARMED);
	// testing below
	// connect(ArmedIndicator, &QPushButton::clicked, this, &MainWindow::OnArmedButtonPressed);

	InitiateButton->setText(tr("Initiate"));

	AbortButton->setText(tr("Abort"));
	AbortButton->setStyleSheet("color: red");

	AbortFont.setBold(true);
} // void MainWindow::SetupButtons()

void MainWindow::SetupActionsRow() {
	ActionsRow = new QGroupBox();
	ActionsRow->setObjectName("statusColumn");

	SetGroupBoxStatus(ActionsRow, Status::DISARMED);

	MajorLayout->addWidget(ActionsRow, 1, 0, 1, 2);

	QSizePolicy vhexpanding;
	vhexpanding.setVerticalPolicy(QSizePolicy::MinimumExpanding);
	vhexpanding.setHorizontalPolicy(QSizePolicy::MinimumExpanding);

	StandbyIndicator->setSizePolicy(vhexpanding);
	ActionsRowOrganizer->addWidget(StandbyIndicator);

	ArmedIndicator->setSizePolicy(vhexpanding);
	ActionsRowOrganizer->addWidget(ArmedIndicator);

	InitiateButton->setSizePolicy(vhexpanding);
	ActionsRowOrganizer->addWidget(InitiateButton);

	AbortButton->setSizePolicy(vhexpanding);
	ActionsRowOrganizer->addWidget(AbortButton);

	ActionsRow->setLayout(ActionsRowOrganizer);
} // void MainWindow::SetupActionsRow()

void MainWindow::SetAllButtonTextSize() {
	ButtonFont.setPixelSize(ButtonFontAdjustment.AdjustPxSize(window()));
	StandbyIndicator->setFont(ButtonFont);
	ArmedIndicator->setFont(ButtonFont);
	InitiateButton->setFont(ButtonFont);
	ActionsRow->setFont(ButtonFont);

	AbortFont.setPixelSize(AbortFontAdjustment.AdjustPxSize(window()));
	AbortButton->setFont(AbortFont);
} // void MainWindow::SetAllButtonTextSize()
// }}}

void MainWindow::SetupMultiPlot() {
	Plots = new MultiPlotContainer(this, 3);
	MajorLayout->addWidget(Plots, 0, 0);
	QList<Plot::EmbeddablePlot2D*> allPlots = Plots->GetPlots();

	Plot::AxisInfo axInfo;
	axInfo.Range = { 0, 10 };

	Plot::AxisInfo justWtv;
	justWtv.Range = {-180, 180};
	justWtv.MajorSpacing = 180;
	justWtv.MinorSpacing = 45;

	std::array<std::string, 3> RPY = {"Roll", "Pitch", "Yaw"};
	auto angle = RPY.begin();
	auto color = Plot::STANDARD_COLOR.begin();

	for (Plot::EmbeddablePlot2D* p : allPlots) {
		std::string name = *angle;
		Plot::ColorRGB rgb = color->second;
		Plot::SeriesInfo info;
		info.Name = name;
		info.Color = rgb;

		p->AddSeries(info);

		justWtv.Title = name;
		p->SetAxis(Plot::Axis::QUANTITY, justWtv);
		p->SetAxis(Plot::Axis::TIME, axInfo);

		angle++;
		color++;
	}
} 

void MainWindow::SetupTimeHistoryPlotQChart() {
	Plot = new Plot::PlotQChart(this);
	MajorLayout->addWidget(Plot, 1, 0);

	Plot::AxisInfo axInfo;
	axInfo.Range = { 0, 10 };
	axInfo.MajorSpacing = 1;
	axInfo.MinorSpacing = 0.5;
	Plot->SetAxis(Plot::Axis::TIME, axInfo);

	Plot::SeriesInfo rollInfo;
	rollInfo.Name = "Roll";
	rollInfo.Color = Plot::STANDARD_COLOR.at("Red");

	Plot::SeriesInfo pitchInfo;
	pitchInfo.Name = "Pitch";
	pitchInfo.Color = Plot::STANDARD_COLOR.at("Green");

	Plot::SeriesInfo yawInfo;
	yawInfo.Name = "Yaw";
	yawInfo.Color = Plot::STANDARD_COLOR.at("Blue");

	Plot->AddSeries(rollInfo);
	Plot->AddSeries(pitchInfo);
	Plot->AddSeries(yawInfo);

	StupidMakeData(Plot);
} // void MainWindow::SetupTimeHistoryPlotQChart()
// }}}
// Menubar and Actions {{{
void MainWindow::About() {
    QMessageBox::about(this, tr("About"),
            tr("This is a recreation of the original UI layout provided."));
} // void MainWindow::About()

void MainWindow::CreateMenus() {
    FileMenu = menuBar()->addMenu(tr("&File"));
    FileMenu->addSeparator();
    FileMenu->addAction(ExitAct);

    EditMenu = menuBar()->addMenu(tr("&Edit"));

    HelpMenu = menuBar()->addMenu(tr("&Help"));
    HelpMenu->addAction(AboutAct);
} // void MainWindow::CreateMenus()

void MainWindow::CreateActions() {
    ExitAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit),
                          tr("Exit"), this);
    ExitAct->setShortcuts(QKeySequence::Quit);
    ExitAct->setStatusTip(tr("Exit the application"));
    connect(ExitAct, &QAction::triggered, this, &QWidget::close);

	AboutAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout),
                           tr("&About"), this);
    AboutAct->setStatusTip(tr("Show the application's About box"));
    connect(AboutAct, &QAction::triggered, this, &MainWindow::About);
} // void MainWindow::CreateActions()

void MainWindow::OnArmedButtonPressed() {
	ArmedButtonActive = !ArmedButtonActive;
	
	if (ArmedButtonActive) {
		// Armed state - Red
		ArmedIndicator->setText(tr("Armed"));
		SetButtonStatus(ArmedIndicator, Status::ARMED);
		SetGroupBoxStatus(ActionsRow, Status::ARMED);
	} else {
		// Disarmed state - Yellow
		ArmedIndicator->setText(tr("Disarmed"));
		SetButtonStatus(ArmedIndicator, Status::DISARMED);
		SetGroupBoxStatus(ActionsRow, Status::DISARMED);
	}
} // void MainWindow::OnArmedButtonPressed()
// }}}
} // namespace VSCL
// vim: foldmethod=marker
