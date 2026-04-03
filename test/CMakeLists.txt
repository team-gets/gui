add_executable(fs_suite "${CMAKE_CURRENT_LIST_DIR}/fs.cpp")
target_include_directories(fs_suite PRIVATE ${STD_APP_INCLUDES})
target_compile_warn_all(fs_suite)

ENABLE_TESTING()
add_test(Filesystem fs_suite)
