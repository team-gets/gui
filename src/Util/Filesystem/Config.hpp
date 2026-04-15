#pragma once

#include "Util/Filesystem/Settings.hpp"

namespace YAML { class Node; }
namespace VSCL::FS {

std::filesystem::path GetConfigFile();
YAML::Node SerializeConfigToYAML(const VSCL::Settings& settings);
void WriteConfig(const VSCL::Settings& settings);

} // namespace VSCL::FS
