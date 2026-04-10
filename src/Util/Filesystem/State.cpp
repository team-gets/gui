#include <fstream>

#include "UserPaths.hpp"
#include "State.hpp"

static constexpr std::string_view
DO_NOT_MODIFY_NOTICE = "# THIS FILE HAS BEEN GENERATED AUTOMATICALLY.\n"
					   "# IT IS NOT RECOMMENDED TO MODIFY THIS FILE.\n";

namespace VSCL::FS {

void PushYAMLIntoFile(const YAML::Node& yamlin, const std::string_view& name) {
	constexpr std::string_view subdir = GetStandardPath("config");
	const std::filesystem::path appsdata = GetUserAppData();
	std::ofstream streem(appsdata / subdir / name);

	streem << DO_NOT_MODIFY_NOTICE;
	streem << yamlin;
}
} // namespace VSCL
