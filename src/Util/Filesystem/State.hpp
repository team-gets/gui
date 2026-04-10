#pragma once

#include <filesystem>
#include <chrono>
#include "yaml-cpp/yaml.h"

namespace VSCL {

struct State {
	std::filesystem::path LatestSocket;
};

namespace FS {

void PushYAMLIntoFile(const YAML::Node& yamlin, const std::string_view& name);

}} // namespace VSCL::FS
