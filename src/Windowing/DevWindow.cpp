#include <filesystem>
#include <iostream>

#include <QFileDialog>

#include "DevWindow.h"
#include "../Widgets/Dial/AttitudeDial.h"

namespace VSCL {
DevWindow::DevWindow() {
    QWidget* widget = new QWidget;
    setCentralWidget(widget);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    widget->setLayout(layout);

    MainQuick = new QQuickWidget;
	layout->addWidget(MainQuick);
	MainQuick->setVisible(false);

	AttitudeDial* dial = new AttitudeDial(this);
	NumericTestWidget* NumericDisplaysTest = new NumericTestWidget(this, dial, [dial](int newValue) { dial->SetDialAngle(newValue); });
	layout->addWidget(NumericDisplaysTest);
	NumericDisplaysTest->setVisible(true);

    CreateActions();
    CreateMenus();

    QString message = tr("Howdy");
    statusBar()->showMessage(message);

    setWindowTitle(tr("VSCL Gyroscopic Test Rig"));
    setMinimumSize(160, 160);
    resize(720, 480);
} // void DevWindow::DevWindow()

void DevWindow::SetQMLFromPath(const QUrl& path) {
	MainQuick->setSource(path);
	CurrentQML = path;
}

void DevWindow::SwapSetting() {
	switch (CurrentSetting) {
	case DevWindow::NumericTesting:
		NumericDisplaysTest->setVisible(false);
		MainQuick->setVisible(true);
		CurrentSetting = DevWindow::QMLView;
		break;
	case DevWindow::QMLView:
		MainQuick->setVisible(false);
		NumericDisplaysTest->setVisible(true);
		CurrentSetting = DevWindow::NumericTesting;
		break;
	}
}

void DevWindow::OpenQML() {
	std::string currentWd = std::filesystem::current_path().string();
	const char* cwd = currentWd.c_str();
	QUrl qmlPath = QFileDialog::getOpenFileUrl(this,
		tr("Open QML Source"), QUrl::fromLocalFile(cwd),
		tr("QML Sources (*.qml)"));

	SetQMLFromPath(qmlPath);
} // void DevWindow::OpenQML()

void DevWindow::ReloadQML() {
	SetQMLFromPath(CurrentQML);
} // void DevWindow::ReloadQML()

void DevWindow::About() {
    QMessageBox::about(this, tr("About"),
            tr("Currently in development mode."));
} // void DevWindow::About()

void DevWindow::CreateMenus() {
    FileMenu = menuBar()->addMenu(tr("&File"));
    FileMenu->addAction(QMLLoadAct);
    FileMenu->addAction(SwapSettingAct);
    FileMenu->addSeparator();
    FileMenu->addAction(ExitAct);

    EditMenu = menuBar()->addMenu(tr("&Edit"));
    EditMenu->addAction(ReloadAct);

    HelpMenu = menuBar()->addMenu(tr("&Help"));
    HelpMenu->addAction(AboutAct);
} // void DevWindow::CreateMenus()

void DevWindow::CreateActions() {
	QMLLoadAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen),
							 tr("Load QML"), this);
	QMLLoadAct->setShortcuts(QKeySequence::Open);
	QMLLoadAct->setStatusTip(tr("Load QML into the viewport."));
	connect(QMLLoadAct, &QAction::triggered, this, &DevWindow::OpenQML);

	SwapSettingAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen),
							 tr("Change Setting"), this);
	SwapSettingAct->setShortcuts(QKeySequence::NextChild);
	SwapSettingAct->setStatusTip(tr("Change between QML viewport and numeric testing modes"));
	connect(SwapSettingAct, &QAction::triggered, this, &DevWindow::SwapSetting);

    ExitAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit),
                          tr("Exit"), this);
    ExitAct->setShortcuts(QKeySequence::Quit);
    ExitAct->setStatusTip(tr("Exit the application"));
    connect(ExitAct, &QAction::triggered, this, &QWidget::close);

    ReloadAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::EditRedo),
                          tr("Reload"), this);
    ReloadAct->setShortcuts(QKeySequence::Redo);
    ReloadAct->setStatusTip(tr("Reload QML sources"));
    connect(ReloadAct, &QAction::triggered, this, &DevWindow::ReloadQML);

	AboutAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout),
                           tr("&About"), this);
    AboutAct->setStatusTip(tr("Show the application's About box"));
    connect(AboutAct, &QAction::triggered, this, &DevWindow::About);
} // void DevWindow::CreateActions()
} // namespace VSCL
