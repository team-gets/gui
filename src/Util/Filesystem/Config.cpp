#include <fstream>

#include "yaml-cpp/yaml.h"

#include "Util/Filesystem/UserPaths.hpp"
#include "Config.hpp"

namespace stdfs = std::filesystem;

namespace VSCL::FS {
stdfs::path GetConfigFile() {
	constexpr std::string_view cfgwhere = GetStandardPath("config");
	return GetUserAppData() / cfgwhere / "config.yaml";
}

YAML::Node SerializeConfigToYAML(const VSCL::Settings& settings) {
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

	return top_lvl;
}

VSCL::Settings DeserializeConfigFromYAML(const YAML::Node& serialized) {
	if (!serialized["Data"] && !serialized["Connection"]) return VSCL::Settings{};

	const YAML::Node& data = serialized["Data"];
	const YAML::Node& conn = serialized["Connection"];

	return VSCL::Settings {
		.Data {
			.OutputDirectory = stdfs::path(data["OutputDirectory"].as<std::string>()),
			.LogPrefix = data["LogPrefix"].as<std::string>(),
		},
		.Connect {
			.DefaultInterface = conn["DefaultInterface"].as<std::string>(),
			.DefaultGatewayPort = conn["DefaultGatewayPort"].as<std::string>(),
		},
	};
}

void WriteConfig(const VSCL::Settings& settings) {
	YAML::Node yamlized = SerializeConfigToYAML(settings);

	stdfs::path cfgpath = GetConfigFile();
	std::ofstream cfg(cfgpath);
	cfg << yamlized;
}

VSCL::Settings ReadConfig(const std::filesystem::path& path) {
	YAML::Node yamlized = YAML::LoadFile(path.string());
	return DeserializeConfigFromYAML(yamlized);
}
} // namespace VSCL::FS
