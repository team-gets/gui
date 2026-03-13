#include <QFileDialog>

#include "WidgetsRecreation.h"
#include "Plotting/Backend/GR.h"

namespace VSCL::FromPpt {
Widgets::Widgets() {
	Plot::PlotGR* grplotted = new Plot::PlotGR(this);
	PlotContainer = new Plot::PlotContainer(this, grplotted);
	setCentralWidget(PlotContainer);

    CreateActions();
    CreateMenus();

    QString message = tr("Howdy");
    statusBar()->showMessage(message);

    setWindowTitle(tr("VSCL Gyroscopic Test Rig"));
    setMinimumSize(160, 160);
    resize(720, 480);
} // void Widgets::Widgets()
void Widgets::About() {
    QMessageBox::about(this, tr("About"),
            tr("Currently in development mode."));
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
} // namespace VSCL::FromPpt
