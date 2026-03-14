
#include "WidgetsRecreation.h"
#include "Plotting/Backend/GR.h"

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

} // void Widgets::Widgets()

// Layout and Widgets Setup {{{
void Widgets::SetupCentralWidget() {
	MajorContainer = new QWidget(this);

	QSizePolicy majorPolicy;
	majorPolicy.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
	majorPolicy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
	MajorContainer->setSizePolicy(majorPolicy);

	MajorLayout = new QGridLayout(MajorContainer);
	MajorLayout->setContentsMargins(10, 10, 10, 10);
	MajorContainer->setLayout(MajorLayout);

	setCentralWidget(MajorContainer);
} // void Widgets::SetupCentralWidget()

void Widgets::SetupAttitudeDials() {
	AttitudeDialRow = new QFrame(MajorContainer);
	MajorLayout->addWidget(AttitudeDialRow, 0, 0);

	AttitudeDialOrganizer = new QHBoxLayout(AttitudeDialRow);
	AttitudeDialOrganizer->setContentsMargins(10, 10, 10, 10);
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

void Widgets::SetupTimeHistoryPlot() {
	Plot = new Plot::PlotGR(this);
	TimeHistory = new Plot::PlotContainer(MajorContainer, Plot);
	MajorLayout->addWidget(TimeHistory, 1, 0);

	Plot->AddSeries();
	Plot->AddSeries();
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
