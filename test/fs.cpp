/*
 *	Test on Filesystem Utilities
 */

#include <iostream>
#include "Util/UserPaths.hpp"

int main(int argc, char** argv) {
	// Test user perms to make em pretty much
	std::cout << "Checking where application paths are... ";
	std::filesystem::path whereapp = VSCL::FS::GetUserAppData();
	std::cout << whereapp << "\n";
	
	std::cout << "Making standard paths... ";
	bool success = VSCL::FS::MakeStandardAppPaths();
	std::cout << ((success) ? "Done!\n" : "Failed...\n");

	return (success) ? 0 : -1;
}
