add_library(fs_utils STATIC
	"${CMAKE_CURRENT_LIST_DIR}/UserPaths.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/DataIO.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Config.cpp")

target_link_libraries(fs_utils PUBLIC yaml-cpp::yaml-cpp)
target_include_directories(fs_utils PUBLIC ${STD_APP_INCLUDES})
target_compile_warn_all(fs_utils)
add_library(VSCL::FS ALIAS fs_utils)
