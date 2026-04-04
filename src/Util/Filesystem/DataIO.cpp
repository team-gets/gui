#include <filesystem>
#include <algorithm>
#include <format>
#include <chrono>

#include "Util/Filesystem/UserPaths.hpp"
#include "DataIO.hpp"

namespace chrono = std::chrono;
namespace fs = std::filesystem;

namespace VSCL::FS {
static std::string MakeTimestamp(void) {
	chrono::time_point rn = chrono::floor<chrono::seconds>(chrono::utc_clock::now());
	return std::format("{:%FT%H_%M_%S}", rn);
}

static void WriteCSVRow(std::ofstream& output, const std::vector<std::string> row) {
	const std::string last = *(row.end() - 1);
	std::for_each(row.begin(), row.end(),
		[&](const std::string& field){
			output << field;

			if (last != field) {
				output << ",";
			}
			else {
				output << "\n";
			}
	});
}

std::ofstream SetupDataOutput(const std::vector<std::string>& fields, const std::string& prefix) {
	std::string stamped = prefix + MakeTimestamp() + ".csv";
	fs::path loc = GetUserAppData() / "data" / fs::path(stamped);
	std::ofstream output(loc);
	
	WriteCSVRow(output, fields);

	return output;
}

void WriteData(std::ofstream& output, const std::vector<std::string>& data) {
	WriteCSVRow(output, data);
}
} // namespace VSCL::FS
