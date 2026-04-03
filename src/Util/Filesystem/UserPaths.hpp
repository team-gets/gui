#pragma once

#include <array>
#include <string_view>
#include <filesystem>

namespace VSCL::FS {

static constexpr std::array<std::string_view, 2> StandardPaths = {
	"data", "config"
};

std::filesystem::path GetUserAppData();
bool MakeStandardAppPaths();

} // namespace VSCL
