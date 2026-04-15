#include <filesystem>
#include "Util/Filesystem/UserPaths.hpp"

namespace VSCL {
struct DataSettings {
	// Where to output recorded data
	std::filesystem::path OutputDirectory =
		FS::GetUserAppData() / FS::GetStandardPath("config");
	
	// Data csv log prefix
	std::string LogPrefix = "run";
};

struct ConnectSettings {
	std::string DefaultInterface = "CANopen";
	std::string DefaultGatewayPort = "CAN0";
};

struct Settings {
	DataSettings Data;
	ConnectSettings Connect;
};
}
