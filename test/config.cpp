#include <iostream>
#include "Util/Filesystem/Config.hpp"

int main() {
	VSCL::Settings opts;

	std::cout << "Creating new config at " << VSCL::FS::GetConfigPath() << "\n";
	VSCL::FS::SerializeConfig(opts);
	std::cout << "All done!\n";
}
