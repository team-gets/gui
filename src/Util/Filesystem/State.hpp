#pragma once

#include <filesystem>
#include <chrono>
#include "yaml-cpp/yaml.h"

namespace VSCL {

struct State {
	std::filesystem::path LatestSocket;
};

namespace FS {

std::filesystem::path GetStateFile();
YAML::Node SerializeStateToYAML(const VSCL::State& state);
void WriteState(const VSCL::State& state);

}} // namespace VSCL::FS
