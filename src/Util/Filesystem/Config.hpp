#pragma once

#include "Util/Filesystem/Settings.hpp"

namespace VSCL::FS {

std::filesystem::path GetConfigPath();
void SerializeConfig(const VSCL::Settings& settings);

} // namespace VSCL::FS
