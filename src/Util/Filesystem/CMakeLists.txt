add_library(fs_utils SHARED
	"${CMAKE_CURRENT_LIST_DIR}/UserPaths.cpp")

target_include_directories(fs_utils PUBLIC ${CMAKE_CURRENT_LIST_DIR})
add_library(VSCL::FS ALIAS fs_utils)

