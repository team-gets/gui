#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>

#include "UserPaths.hpp"

namespace fs = std::filesystem;

namespace VSCL::FS {

fs::path GetUserAppData() {
	char usrdata[256] = { 0 };
	
	#ifdef _WIN32 // Windows
		size_t ret_size;
		errno_t getenv_stat;

		getenv_stat = getenv_s(&ret_size, usrdata, 128, "LOCALAPPDATA");
		if (getenv_stat != 0 || ret_size == 0) {
			std::cerr << "Did not get %LOCALAPPDATA%\n";
			return fs::temp_directory_path();
		}

	#else // Linux
		const char* xdg = std::getenv("XDG_DATA_HOME");
		if (xdg == NULL || strnlen(xdg, 255) == 0) {
			const char* homer = std::getenv("HOME");
			std::strncpy(usrdata, homer, 255);
			std::strncat(usrdata, "/.local/share", 255);
		}
		else {
			std::strncpy(usrdata, xdg, 255);
		}
	#endif

	fs::path usrdata_as_path(usrdata);
	return usrdata_as_path / "vscl" / "testrig";
} // fs::path GetUserAppData()

bool MakeStandardAppPaths() {
	const fs::path app_dir = GetUserAppData();
	if (!fs::exists(app_dir)) { fs::create_directories(app_dir); }
	bool all_success = true;

	std::for_each(StandardPaths.begin(), StandardPaths.end(),
		[&](const fs::path& subdir) {

		fs::path full_path = app_dir / subdir;
		bool success = true;

		if (!fs::exists(full_path)) {
			success = fs::create_directories(full_path);
		}

		if (!success) {
			std::cerr << "Failed to make the path at " << full_path << "\n";
		}

		all_success = all_success && success;
	});

	return all_success;
} // bool MakeStandardAppPaths()
} // namespace VSCL::FS
