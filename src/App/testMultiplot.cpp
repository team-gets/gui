#include <QApplication>
#include <QWindow>
#include <QWidget>

#include "Widgets/Displays/MultiPlotContainer.hpp"

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	VSCL::MultiPlotContainer window(nullptr, 3);
	
	window.show();
	return app.exec();
}
