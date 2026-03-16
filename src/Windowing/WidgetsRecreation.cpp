#include <cstdlib>
#include <cmath>
#include <chrono>

#include "WidgetsRecreation.h"
#include "Plotting/Backend/GR.h"

// stupid temp thing {{{
static void stupid_make_data(VSCL::Plot::EmbeddablePlot2D* plot) {
	double ph1, ph2, ph3;

	std::srand(std::chrono::system_clock::now().time_since_epoch().count());
	ph1 = std::rand() % 12;
	ph2 = std::rand() % 12;
	ph3 = std::rand() % 12;

	for (int i = 0; i < 100; i++) {
		plot->AddPoint(0, i/10.0, std::cos(0.1 * i + ph1/12) / 2.0 + 0.5);
		plot->AddPoint(1, i/10.0, std::sin(0.1 * i - ph2/12) / 2.0 + 0.5);
		plot->AddPoint(2, i/10.0, std::cos(0.1 * i + ph3/12) / 2.0 + 0.5);
	}
}
// }}}

namespace VSCL::FromPpt {
Widgets::Widgets() {
    // Set up menubar and statusbar
    CreateActions();
    CreateMenus();

    QString message = tr("Test Rig Operations");
    statusBar()->showMessage(message);

	// Geometry and window characteristics
    setWindowTitle(tr("VSCL Gyroscopic Test Rig"));
    setMinimumSize(160, 160);
    resize(720, 480);

	// Set up the static layout
	SetupCentralWidget();
	SetupAttitudeDials();
	SetupTimeHistoryPlot();
	SetupButtons();
	SetupStatusColumn();
	SetGridColumnsMinimums();
	SetGridRowsMinimums();

} // void Widgets::Widgets()

void Widgets::resizeEvent(QResizeEvent* event) {
	SetGridColumnsMinimums();
} // void Widgets::resizeEvent()

// Layout and Widgets Setup {{{
void Widgets::SetupCentralWidget() {
	MajorContainer = new QWidget(this);

	QSizePolicy majorPolicy;
	majorPolicy.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
	majorPolicy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
	MajorContainer->setSizePolicy(majorPolicy);

	MajorLayout = new QGridLayout(MajorContainer);
	MajorLayout->setContentsMargins(40, 40, 40, 40);
	MajorContainer->setLayout(MajorLayout);

	setCentralWidget(MajorContainer);
} // void Widgets::SetupCentralWidget()

void Widgets::SetupAttitudeDials() {
	AttitudeDialRow = new QFrame(MajorContainer);
	MajorLayout->addWidget(AttitudeDialRow, 0, 0);

	AttitudeDialOrganizer = new QHBoxLayout(AttitudeDialRow);
	AttitudeDialOrganizer->setContentsMargins(20, 20, 20, 20);
	AttitudeDialRow->setLayout(AttitudeDialOrganizer);

	QSizePolicy dialsPolicy;
	dialsPolicy.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
	dialsPolicy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
	AttitudeDialRow->setSizePolicy(dialsPolicy);

	RollDial = new AttitudeDial(AttitudeDialRow);
	AttitudeDialOrganizer->addWidget(RollDial);

	PitchDial = new AttitudeDial(AttitudeDialRow);
	AttitudeDialOrganizer->addWidget(PitchDial);

	YawDial = new AttitudeDial(AttitudeDialRow);
	AttitudeDialOrganizer->addWidget(YawDial);

	Dials = { RollDial, PitchDial, YawDial };
} // void Widgets::SetupCentralWidget()

void Widgets::SetGridColumnsMinimums() {
	if (!MajorLayout) { return; };
	const QRect& dims = centralWidget()->geometry();
	MajorLayout->setColumnMinimumWidth(0, 3 * dims.width() / 5);
} // void Widgets::SetGridColumnsMinimums()

void Widgets::SetGridRowsMinimums() {
	if (!MajorLayout) { return; }
	const QRect& dims = centralWidget()->geometry();
	MajorLayout->setRowMinimumHeight(0, 2 * dims.width() / 5);
}

void Widgets::SetupButtons() {
	LoadTestRoutineButton = new QPushButton;
	LoadTestRoutineButton->setText(tr("Load Test Routine"));

	QuantityCalculatorButton = new QPushButton;
	QuantityCalculatorButton->setText(tr("Calculate Quantity"));

	LogOpenButton = new QPushButton;
	LogOpenButton->setText(tr("Open Log"));

	AbortButton = new QPushButton;
	AbortButton->setText(tr("Abort"));
	AbortButton->setStyleSheet(" QPushButton { background-color: red } ");
} // void Widgets::SetupButtons()

void Widgets::SetupStatusColumn() {
	StatusColumn = new QGroupBox(tr("Operate"));
	MajorLayout->addWidget(StatusColumn, 1, 1);

	QSizePolicy vhexpanding;
	vhexpanding.setVerticalPolicy(QSizePolicy::MinimumExpanding);
	vhexpanding.setHorizontalPolicy(QSizePolicy::MinimumExpanding);

	StatusColumnOrganizer = new QVBoxLayout;
	LoadTestRoutineButton->setSizePolicy(vhexpanding);
	StatusColumnOrganizer->addWidget(LoadTestRoutineButton);

	QuantityCalculatorButton->setSizePolicy(vhexpanding);
	StatusColumnOrganizer->addWidget(QuantityCalculatorButton);

	LogOpenButton->setSizePolicy(vhexpanding);
	StatusColumnOrganizer->addWidget(LogOpenButton);

	AbortButton->setSizePolicy(vhexpanding);
	StatusColumnOrganizer->addWidget(AbortButton);

	StatusColumn->setLayout(StatusColumnOrganizer);
} // void Widgets::SetupStatusColumn()

void Widgets::SetupTimeHistoryPlot() {
	Plot = new Plot::PlotGR(this);
	TimeHistory = new Plot::PlotContainer(MajorContainer, Plot);
	MajorLayout->addWidget(TimeHistory, 1, 0);

	Plot::AxisInfo axInfo;
	axInfo.Range = { 0, 10 };
	axInfo.MajorSpacing = 10;
	axInfo.MinorSpacing = 0.25;
	Plot->SetAxis(Plot::Axis::Time, axInfo);

	Plot::SeriesInfo rollInfo;
	rollInfo.Name = "Roll";
	rollInfo.Color = Plot::RGBFromColorGR(Plot::ColorGR::Red);

	Plot::SeriesInfo pitchInfo;
	pitchInfo.Name = "Pitch";
	pitchInfo.Color = Plot::RGBFromColorGR(Plot::ColorGR::Blue);

	Plot::SeriesInfo yawInfo;
	yawInfo.Name = "Yaw";
	yawInfo.Color = Plot::RGBFromColorGR(Plot::ColorGR::Green);

	Plot->SetSeries(0, rollInfo);
	Plot->AddSeries(pitchInfo);
	Plot->AddSeries(yawInfo);

	stupid_make_data(Plot);
} // void Widgets::SetupTimeHistoryPlot()
// }}}
// Menubar and Actions {{{
void Widgets::About() {
    QMessageBox::about(this, tr("About"),
            tr("This is a recreation of the original UI layout provided."));
} // void Widgets::About()

void Widgets::CreateMenus() {
    FileMenu = menuBar()->addMenu(tr("&File"));
    FileMenu->addSeparator();
    FileMenu->addAction(ExitAct);

    EditMenu = menuBar()->addMenu(tr("&Edit"));

    HelpMenu = menuBar()->addMenu(tr("&Help"));
    HelpMenu->addAction(AboutAct);
} // void Widgets::CreateMenus()

void Widgets::CreateActions() {
    ExitAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit),
                          tr("Exit"), this);
    ExitAct->setShortcuts(QKeySequence::Quit);
    ExitAct->setStatusTip(tr("Exit the application"));
    connect(ExitAct, &QAction::triggered, this, &QWidget::close);

	AboutAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout),
                           tr("&About"), this);
    AboutAct->setStatusTip(tr("Show the application's About box"));
    connect(AboutAct, &QAction::triggered, this, &Widgets::About);
} // void Widgets::CreateActions()
// }}}
} // namespace VSCL::FromPpt
// vim: foldmethod=marker
