#pragma once

#include <array>
#include <string_view>
#include <filesystem>

namespace VSCL::FS {

static constexpr std::array<std::string_view, 3> StandardPaths = {
	"data", "config", "script"
};

std::filesystem::path GetUserAppData();
bool MakeStandardAppPaths();

} // namespace VSCL
