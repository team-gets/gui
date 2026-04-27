#include <QApplication>
#include <QWindow>
#include <QWidget>
#include <fstream>

#include "Windowing/MainWindow.hpp"
#include "Util/Filesystem/Config.hpp"
#include "Util/Filesystem/State.hpp"

namespace fs = std::filesystem;

static VSCL::Settings settings{};
static VSCL::State state{};

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	fs::path cfg = VSCL::FS::GetConfigFile();
	if (!fs::is_regular_file(cfg)) {
		std::ofstream streem(cfg.string());
		streem << VSCL::FS::SerializeConfigToYAML(settings);
	}
	else {
		settings = VSCL::FS::ReadConfig(cfg);
	}

	fs::path stat = VSCL::FS::GetStateFile();
	if (!fs::is_regular_file(stat)) {
		std::ofstream streem(stat.string());
		streem << VSCL::FS::SerializeStateToYAML(state);
	}

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
