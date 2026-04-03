add_executable(fs_suite "${CMAKE_CURRENT_LIST_DIR}/fs.cpp")
target_include_directories(fs_suite PRIVATE ${STD_APP_INCLUDES})

add_test(Filesystem fs_suite)
