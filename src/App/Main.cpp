#include <QApplication>
#include <QWindow>
#include <QWidget>

#include "Windowing/MainWindow.hpp"

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	VSCL::MainWindow window;

    QString message = window.tr("Test Rig Operations");
    window.statusBar()->showMessage(message);

    window.setWindowTitle(window.tr("VSCL Gyroscopic Test Rig"));
    window.setMinimumSize(
    	VSCL::Util::MINIMUM_WIDTH, VSCL::Util::MINIMUM_HEIGHT);

    window.resize(VSCL::Util::MINIMUM_WIDTH, VSCL::Util::MINIMUM_HEIGHT);

	window.show();
	return app.exec();
}
