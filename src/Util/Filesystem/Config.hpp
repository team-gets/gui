#pragma once

#include "Util/Filesystem/Settings.hpp"

namespace YAML { class Node; }
namespace VSCL::FS {

std::filesystem::path GetConfigFile();
YAML::Node SerializeConfigToYAML(const VSCL::Settings& settings);
VSCL::Settings DeserializeConfigFromYAML(const YAML::Node& serialized);

void WriteConfig(const VSCL::Settings& settings);
VSCL::Settings ReadConfig(const std::filesystem::path& path);

} // namespace VSCL::FS
