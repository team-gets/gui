#include <iostream>
#include <filesystem>
#include <fstream>
#include "Util/Filesystem/State.hpp"

namespace fs = std::filesystem;

int main() {
	VSCL::State opts;

	fs::path statef = VSCL::FS::GetStateFile();
	std::cout << "Creating new state at " << statef << "\n";
	VSCL::FS::WriteState(opts);
	std::cout << "Done writing!\n";

	bool exists = fs::is_regular_file(statef);
	std::cout << "Does it exist? ";
	
	if (exists) {
		std::cout << "Yes!\n";
	}
	else {
		std::cout << "No!\n";
		return 1;
	}

	std::cout << "These are the contents:\n\n";
	std::ifstream streem(statef);
	std::cout << streem.rdbuf() << "\n\n";

	return 0;

}
