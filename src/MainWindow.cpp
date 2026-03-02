#include <filesystem>

#include <QFileDialog>

#include "MainWindow.h"

namespace Gets {
MainWindow::MainWindow() {
    QWidget* widget = new QWidget;
    setCentralWidget(widget);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    widget->setLayout(layout);

    MainQuick = new QQuickWidget;
    layout->addWidget(MainQuick);

    CreateActions();
    CreateMenus();

    QString message = tr("Howdy");
    statusBar()->showMessage(message);

    setWindowTitle(tr("VSCL Gyroscopic Test Rig"));
    setMinimumSize(160, 160);
    resize(720, 480);
} // void MainWindow::MainWindow()

void MainWindow::SetQMLFromPath(const QUrl& path) {
	MainQuick->setSource(path);
	CurrentQML = path;
}

void MainWindow::OpenQML() {
	const char* cwd = std::filesystem::current_path().c_str();
	QUrl qmlPath = QFileDialog::getOpenFileUrl(this,
		tr("Open QML Source"), QUrl::fromLocalFile(cwd),
		tr("QML Sources (*.qml)"));

	SetQMLFromPath(qmlPath);
} // void MainWindow::OpenQML()

void MainWindow::ReloadQML() {
	SetQMLFromPath(CurrentQML);
} // void MainWindow::ReloadQML()

void MainWindow::About() {
    QMessageBox::about(this, tr("About Menu"),
            tr("Welcome"));
} // void MainWindow::About()

void MainWindow::CreateMenus() {
    FileMenu = menuBar()->addMenu(tr("&File"));
    FileMenu->addAction(QMLLoadAct);
    FileMenu->addSeparator();
    FileMenu->addAction(ExitAct);

    EditMenu = menuBar()->addMenu(tr("&Edit"));
    EditMenu->addAction(ReloadAct);

    HelpMenu = menuBar()->addMenu(tr("&Help"));
    HelpMenu->addAction(AboutAct);
} // void MainWindow::CreateMenus()

void MainWindow::CreateActions() {
	QMLLoadAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen),
							 tr("Load QML"), this);
	QMLLoadAct->setShortcuts(QKeySequence::Open);
	QMLLoadAct->setStatusTip(tr("Load QML into the viewport."));
	connect(QMLLoadAct, &QAction::triggered, this, &MainWindow::OpenQML);

    ExitAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit),
                          tr("Exit"), this);
    ExitAct->setShortcuts(QKeySequence::Quit);
    ExitAct->setStatusTip(tr("Exit the application"));
    connect(ExitAct, &QAction::triggered, this, &QWidget::close);

    ReloadAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::EditRedo),
                          tr("Reload"), this);
    ReloadAct->setShortcuts(QKeySequence::Redo);
    ReloadAct->setStatusTip(tr("Reload QML sources"));
    connect(ReloadAct, &QAction::triggered, this, &MainWindow::ReloadQML);

	AboutAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout),
                           tr("&About"), this);
    AboutAct->setStatusTip(tr("Show the application's About box"));
    connect(AboutAct, &QAction::triggered, this, &MainWindow::About);
} // void MainWindow::CreateActions()
} // namespace Gets
