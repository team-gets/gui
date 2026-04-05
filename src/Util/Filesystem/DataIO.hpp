#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <type_traits>
#include "Util/Filesystem/API.hpp"

namespace VSCL::FS {

/*
 *	Open an output filestream to a timestampped CSV file.
 */
std::ofstream FS_API SetupDataOutput(const std::vector<std::string>& fields, const std::string& prefix = "run_");

/*
 *	Write a single row to a CSV filestream.
 */
template<typename T>
static void WriteCSVRow(std::ofstream& output, const std::vector<T>& row) {
	static_assert(
		std::is_floating_point<T>()
		|| std::is_same<std::string, T>()
		|| std::is_same<std::string_view, T>());

	const T last = *(row.end() - 1);
	std::for_each(row.begin(), row.end(),
		[&](const T& field){
			output << field;

			if (last != field) {
				output << ",";
			}
			else {
				output << "\n";
			}
	});
} // static void WriteCSVRow()
} // namespace VSCL::FS
