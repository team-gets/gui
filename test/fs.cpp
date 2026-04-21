/*
 *	Test on Filesystem Utilities
 */

#include <iostream>
#include <string_view>
#include <algorithm>
#include <format>

#include "Util/Filesystem/UserPaths.hpp"
#include "yaml-cpp/yaml.h"

static constexpr std::string_view CONFIG_PATH_NAME = VSCL::FS::GetStandardPath("config");
static void CoutManyNames(void) {
	std::ranges::for_each(VSCL::FS::STANDARD_PATHS, [](const std::string_view& str){
		std::cout << str << "\n";
	});
}

int main(void) {
	// Test user perms to make em pretty much
	std::cout << "Checking where application paths are... ";
	std::filesystem::path whereapp = VSCL::FS::GetUserAppData();
	std::cout << whereapp << "\n";
	
	std::cout << "Making standard paths... ";
	bool success = VSCL::FS::MakeStandardAppPaths();
	std::cout << ((success) ? "Done!\n" : "Failed...\n");

	std::cout << "Here are some standard paths by name...\n";
	std::cout << std::format("Constexprable! {}\n", CONFIG_PATH_NAME);
	CoutManyNames();

	std::cout << "Checking for path existences: \n";
	std::for_each(VSCL::FS::STANDARD_PATHS.begin(), VSCL::FS::STANDARD_PATHS.end(),
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
