#include <QApplication>
#include <QWindow>
#include <QWidget>

#include "Windowing/WidgetsRecreation.hpp"

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	VSCL::FromPpt::Widgets window;
	window.show();
	return app.exec();
}
