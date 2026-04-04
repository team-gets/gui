#pragma once

#include <fstream>
#include <vector>
#include <string>
#include "Util/Filesystem/API.hpp"

namespace VSCL::FS {

struct DataStream {
	std::ofstream Output;
	std::vector<std::string> Fields;
};

std::ofstream FS_API SetupDataOutput(const std::vector<std::string>& fields, const std::string& prefix = "run_");
void FS_API WriteData(std::ofstream& output, const std::vector<std::string>& data);

} // namespace VSCL::FS
