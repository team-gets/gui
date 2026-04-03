add_executable(fs_suite "${CMAKE_CURRENT_LIST_DIR}/fs.cpp")
target_include_directories(fs_suite PRIVATE ${STD_APP_INCLUDES})
target_link_libraries(fs_suite PRIVATE yaml-cpp)
target_link_libraries(fs_suite PRIVATE VSCL::FS)
target_compile_definitions(plotting_iface PRIVATE COMPILING_FS_API_DLL)
target_compile_warn_all(fs_suite)

ENABLE_TESTING()
add_test(Filesystem fs_suite)
