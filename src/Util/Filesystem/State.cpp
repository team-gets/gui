#include <fstream>
#include "UserPaths.hpp"
#include "State.hpp"

namespace stdfs = std::filesystem;
static constexpr std::string_view
DO_NOT_MODIFY_NOTICE = "# THIS FILE HAS BEEN GENERATED AUTOMATICALLY.\n"
					   "# IT IS NOT RECOMMENDED TO MODIFY THIS FILE.\n";

namespace VSCL::FS {

stdfs::path GetStateFile() {
	constexpr std::string_view statewhere = GetStandardPath("config");
	return GetUserAppData() / statewhere / "state-latest.yaml";
}

YAML::Node SerializeStateToYAML(const VSCL::State& state) {
	YAML::Node top_lvl;
	top_lvl["LatestSocket"] = state.LatestSocket.string();

	return top_lvl;
}

void WriteState(const VSCL::State& state) {
	const std::filesystem::path appsdata = GetUserAppData();
	std::ofstream streem(GetStateFile());

	streem << DO_NOT_MODIFY_NOTICE;
	streem << SerializeStateToYAML(state);
}
} // namespace VSCL
