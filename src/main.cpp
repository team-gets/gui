#include <QApplication>
#include <QWindow>
#include <QWidget>

#include "MainWindow/MainWindow.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	VSCL::MainWindow window;
	if (argc > 1) { window.SetQMLFromPath(QUrl::fromLocalFile(argv[1])); }

	window.show();

	return app.exec();
}
