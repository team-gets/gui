#include <QApplication>
#include <QWindow>
#include <QWidget>

#include "Windowing/WidgetsRecreation.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	VSCL::FromPpt::Widgets window;
	window.show();
	return app.exec();
}
