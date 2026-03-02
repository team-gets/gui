#include <QApplication>
#include <QWindow>
#include <QWidget>

#include "MainWindow.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	Gets::MainWindow window;
	window.show();

	return app.exec();
}
