#pragma once

#include <filesystem>

namespace VSCL {
struct Settings {
	std::filesystem::path OutputDirectory;
	bool Autosetup;
};

namespace FS {

}} // namespace VSCL::FS
