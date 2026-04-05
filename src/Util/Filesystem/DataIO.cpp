#include <filesystem>
#include <algorithm>
#include <format>
#include <chrono>

#include "Util/Filesystem/UserPaths.hpp"
#include "DataIO.hpp"

namespace chrono = std::chrono;
namespace fs = std::filesystem;

namespace VSCL::FS {

/*
 *	ISO formatted timestamp
 */
static std::string MakeTimestamp(void) {
	chrono::time_point rn = chrono::floor<chrono::seconds>(chrono::utc_clock::now());
	return std::format("{:%FT%H_%M_%S}", rn);
}

std::ofstream SetupDataOutput(const std::vector<std::string>& fields, const std::string& prefix) {
	std::string stamped = prefix + MakeTimestamp() + ".csv";
	fs::path loc = GetUserAppData() / "data" / fs::path(stamped);
	std::ofstream output(loc);
	
	WriteCSVRow<std::string>(output, fields);

	return output;
}
} // namespace VSCL::FS
