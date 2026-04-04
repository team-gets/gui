add_library(fs_utils SHARED
	"${CMAKE_CURRENT_LIST_DIR}/UserPaths.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/DataIO.cpp")

target_include_directories(fs_utils PUBLIC ${STD_APP_INCLUDES})
target_compile_definitions(fs_utils PRIVATE COMPILING_FS_DLL)
add_library(VSCL::FS ALIAS fs_utils)
