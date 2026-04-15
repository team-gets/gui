#include <iostream>
#include <filesystem>
#include <fstream>
#include "Util/Filesystem/Config.hpp"

namespace fs = std::filesystem;

int main() {
	VSCL::Settings opts;

	fs::path cfgf = VSCL::FS::GetConfigFile();
	std::cout << "Creating new config at " << cfgf << "\n";
	VSCL::FS::WriteConfig(opts);
	std::cout << "Done writing!\n";

	bool exists = fs::is_regular_file(cfgf);
	std::cout << "Does it exist? ";
	
	if (exists) {
		std::cout << "Yes!\n";
	}
	else {
		std::cout << "No!\n";
		return 1;
	}

	std::cout << "These are the contents:\n\n";
	std::ifstream streem(cfgf);
	std::cout << streem.rdbuf() << "\n\n";

	return 0;
}
