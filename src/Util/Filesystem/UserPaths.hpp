#pragma once

#include <array>
#include <string_view>
#include <filesystem>
#include <algorithm>
#include <cstdint>

namespace VSCL::FS {

enum class UserPath : uint8_t {
	Data, Config, Script
};

static constexpr std::array<std::string_view, 3> StandardPaths = {
	"data", "config", "script"
};

static constexpr std::string_view GetStandardPath(const std::string_view& path) {
	return *std::ranges::find(StandardPaths, path);
}

std::filesystem::path GetUserAppData();
bool MakeStandardAppPaths();

} // namespace VSCL
