/*
 *	Test on Filesystem Utilities
 */

#include <iostream>
#include "Util/UserPaths.hpp"

int main(int argc, char** argv) {
	std::cout << "Making standard paths...\n";
	// Test user perms
	return VSCL::FS::MakeStandardAppPaths();
}
