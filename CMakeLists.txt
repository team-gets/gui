cmake_minimum_required(VERSION 3.30...4.0)

project(rig_gui
	LANGUAGES CXX C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_AUTOMOC ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Widgets QuickWidgets Charts)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(FetchContent)
include("./cmake/cpp.cmake")

qt_standard_project_setup(REQUIRES 6.10)
find_package(yaml-cpp)

add_subdirectory("${UTIL_SRC_DIR}/Filesystem")
add_subdirectory("${PLOTTING_SRC_DIR}")

qt_add_executable(testrig_gui WIN32
	${APP_SOURCES} ${WIDGET_SOURCES})
target_include_directories(testrig_gui PRIVATE ${STD_APP_INCLUDES})
target_compile_warn_all(testrig_gui)
target_link_libraries(testrig_gui PRIVATE VSCL::Plot::QChart)
target_link_libraries(testrig_gui PRIVATE ${STD_APP_QT6_DEPS})
add_executable(VSCL::TestrigGUI ALIAS testrig_gui)

add_subdirectory("${CMAKE_SOURCE_DIR}/test")
