#pragma once

#include <fstream>
#include <vector>
#include <string>
#include "Util/Filesystem/API.hpp"

namespace VSCL::FS {

/*
 *	Open an output filestream to a timestampped CSV file.
 */
std::ofstream FS_API SetupDataOutput(const std::vector<std::string>& fields, const std::string& prefix = "run_");

/*
 *	Write data to a CSV filestream.
 */
void FS_API WriteData(std::ofstream& output, const std::vector<std::string>& data);

} // namespace VSCL::FS
