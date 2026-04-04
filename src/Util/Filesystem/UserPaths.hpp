#pragma once

#include <array>
#include <string_view>
#include <filesystem>
#include "Util/Filesystem/API.hpp"

namespace VSCL::FS {

static constexpr std::array<std::string_view, 3> StandardPaths = {
	"data", "config", "script"
};

std::filesystem::path FS_API GetUserAppData();
bool FS_API MakeStandardAppPaths();

} // namespace VSCL
