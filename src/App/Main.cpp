#include <QApplication>
#include <QWindow>
#include <QWidget>

#include "Windowing/MainWindow.hpp"

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	VSCL::MainWindow window;

	window.show();
	return app.exec();
}
