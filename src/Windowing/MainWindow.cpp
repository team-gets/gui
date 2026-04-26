#include "Windowing/MainWindow.hpp"
#include "Plotting/Backend/CoreQChart.hpp"
#include "Widgets/Displays/StatusCollector.hpp"

namespace VSCL {
MainWindow::MainWindow()
	: MajorContainer(new QWidget)

	, AttitudeDialRow(new QFrame(MajorContainer))
	, RollDial(new CompositeDial(AttitudeDialRow))
	, PitchDial(new CompositeDial(AttitudeDialRow))
	, YawDial(new CompositeDial(AttitudeDialRow))

	, Plots(new MultiPlotContainer(MajorContainer, 3))

	, ActionsRow(new QGroupBox(tr("Operate"), MajorContainer))
	, StandbyIndicator(new QPushButton(ActionsRow))
	, ArmedIndicator(new QPushButton(ActionsRow))
	, InitiateButton(new QPushButton(ActionsRow))
	, AbortButton(new QPushButton(ActionsRow))

	, MajorLayout(new QGridLayout) // Parented when SetupCentralWidget()
	, AttitudeDialOrganizer(new QVBoxLayout(AttitudeDialRow))
	, ActionsRowOrganizer(new QHBoxLayout(ActionsRow))
{
	// Set up the static layout
	SetupCentralWidget();
	SetupAttitudeDials();
	SetupMultiPlot();
	SetupButtons();
	SetupActionsRow();
	SetGridColumnsMinimums();
	SetGridRowsMinimums();

	SetAllButtonTextSize();

    // Set up menubar and statusbar
    CreateActions();
    CreateMenus();
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
} // void MainWindow::SetupCentralWidget()

void MainWindow::SetGridColumnsMinimums() {
	const QRect& dims = centralWidget()->geometry();
	MajorLayout->setColumnMinimumWidth(0,  4 * dims.width() / 5);
	MajorLayout->setColumnMinimumWidth(1, 1 * dims.width() / 5);
} // void MainWindow::SetGridColumnsMinimums()

void MainWindow::SetGridRowsMinimums() {
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
