#include <fstream>

#include "yaml-cpp/yaml.h"

#include "Util/Filesystem/UserPaths.hpp"
#include "Config.hpp"

namespace stdfs = std::filesystem;

namespace VSCL::FS {

stdfs::path GetConfigPath() {
	constexpr std::string_view cfgwhere = GetStandardPath("config");
	return GetUserAppData() / cfgwhere / "config.yaml";
}

void SerializeConfig(const VSCL::Settings &settings) {
	const VSCL::DataSettings& dataset = settings.Data;
	YAML::Node data_node;
	data_node["OutputDirectory"] = dataset.OutputDirectory.string();
	data_node["LogPrefix"] = dataset.LogPrefix;

	const VSCL::ConnectSettings& connset = settings.Connect;
	YAML::Node conn_node;
	conn_node["DefaultGatewayPort"] = connset.DefaultGatewayPort;
	conn_node["DefaultInterface"] = connset.DefaultInterface;

	YAML::Node top_lvl;
	top_lvl["Data"] = data_node;
	top_lvl["Connection"] = conn_node;

	stdfs::path cfgpath = GetConfigPath();
	std::ofstream cfg(cfgpath);
	cfg << top_lvl;
}
} // namespace VSCL::FS
