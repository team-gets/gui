/*
 *	Test on Filesystem Utilities
 */

#include <iostream>
#include "Util/Filesystem/UserPaths.hpp"
#include "yaml-cpp/yaml.h"

int main(void) {
	// Test user perms to make em pretty much
	std::cout << "Checking where application paths are... ";
	std::filesystem::path whereapp = VSCL::FS::GetUserAppData();
	std::cout << whereapp << "\n";
	
	std::cout << "Making standard paths... ";
	bool success = VSCL::FS::MakeStandardAppPaths();
	std::cout << ((success) ? "Done!\n" : "Failed...\n");

	std::cout << "Checking for path existences: \n";
	std::for_each(VSCL::FS::StandardPaths.begin(), VSCL::FS::StandardPaths.end(),
		[&](const std::string_view& apppath){
		std::filesystem::path subdir = whereapp / apppath;
		std::cout << (subdir) << " exists? ";
		
		bool existence = std::filesystem::exists(subdir);
		bool isdir = std::filesystem::is_directory(subdir);

		std::cout
			<< (existence ? "yes, " : "no, ")
			<< (isdir ? "as directory" : "not as directory")
			<< "\n";
	});

	return (success) ? 0 : -1;
}
