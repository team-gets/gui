#include <string_view>

#include <QApplication>
#include <QWindow>
#include <QWidget>

#include "Windowing/DevWindow.h"
#include "Windowing/WidgetsRecreation.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	if (argc > 1) {
		std::string_view whatdo(argv[1]); // all to use the == overload
		if (whatdo == "wrec") {
			VSCL::FromPpt::Widgets window;
			window.show();
			return app.exec();
		}
		else {
			VSCL::DevWindow window;
			window.show();
			return app.exec();
		}
	}
	else {
		VSCL::DevWindow window;
		window.show();
		return app.exec();
	}
}
