#pragma once

#include <array>
#include <string_view>
#include <filesystem>
#include <algorithm>
#include <cstdint>

namespace VSCL::FS {

enum class UserPath : uint8_t {
	DATA, CONFIG, SCRIPT
};

static constexpr std::array<std::string_view, 3> STANDARD_PATHS = {
	"data", "config", "script"
};

static constexpr std::string_view GetStandardPath(const std::string_view& path) {
	return *std::ranges::find(STANDARD_PATHS, path);
}

std::filesystem::path GetUserAppData();
bool MakeStandardAppPaths();

} // namespace VSCL
