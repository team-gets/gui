#include <fstream>

#include "yaml-cpp/yaml.h"

#include "Util/Filesystem/UserPaths.hpp"
#include "Config.hpp"

namespace VSCL::FS {

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

	constexpr std::string_view cfgwhere = GetStandardPath("config");
	std::filesystem::path cfgpath = GetUserAppData() / cfgwhere;

	std::ofstream cfg;
	cfg << top_lvl;
}
} // namespace VSCL::FS
