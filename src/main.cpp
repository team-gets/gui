#include <QApplication>
#include <QWindow>
#include <QWidget>

#include "MainWindow.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	Gets::MainWindow window;
	if (argc > 1) { window.SetQMLFromPath(QUrl::fromLocalFile(argv[1])); }

	window.show();

	return app.exec();
}
