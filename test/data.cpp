#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <chrono>

#include "Util/Filesystem/DataIO.hpp"

namespace chrono = std::chrono;

int main(void) {
	std::cout << "Attempting to create a new CSV...\n";
	std::ofstream output = VSCL::FS::SetupDataOutput({ "time", "roll", "pitch", "yaw" });

	std::cout << "Writing preset data...\n";
	VSCL::FS::WriteData(output, { "0.0", "0.0", "10.0", "100.0" });
	VSCL::FS::WriteData(output, { "1.0", "2.0", "50.0", "0.0" });
	VSCL::FS::WriteData(output, { "2.0", "32.0", "67.0", "-123.0" });

	std::cout << "Writing random data... ";
	chrono::time_point rn = chrono::utc_clock::now();

	for (int j = 0; j < 1000; j++) {
		std::srand(std::chrono::utc_clock::now().time_since_epoch().count());
		std::vector<std::string> stuff(4);
		stuff[0] = std::to_string(j + 3) + ".0";
		for (int i = 1; i < 4; i++) {
			stuff[i] = std::to_string(std::rand() % 180 * std::pow(-1, std::rand()));
		}

		VSCL::FS::WriteData(output, stuff);
	}

	chrono::time_point taken = chrono::utc_clock::now();
	std::cout << "I took " << chrono::duration_cast<chrono::milliseconds>(taken - rn) << " for 1000 additional lines!\n";
}
