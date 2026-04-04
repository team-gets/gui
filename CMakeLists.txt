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
include("./cmake/qml.cmake")

qt_standard_project_setup(REQUIRES 6.10)
find_package(yaml-cpp)

add_subdirectory("${UTIL_SRC_DIR}/Filesystem")
add_subdirectory("${PLOTTING_SRC_DIR}")

# Widgets Recreation
qt_add_executable(widgets_recreation WIN32 MACOSX_BUNDLE
	"${WINDOWING_SRC_DIR}/WidgetsRecreation.cpp"
	${OTHER_APP_SOURCES} ${WIDGET_SOURCES})

target_include_directories(widgets_recreation PRIVATE ${STD_APP_INCLUDES})
target_compile_warn_all(widgets_recreation)

target_link_libraries(widgets_recreation PRIVATE ${STD_APP_QT6_DEPS})
target_link_libraries(widgets_recreation PRIVATE VSCL::Plot::QChart)

add_subdirectory("${CMAKE_SOURCE_DIR}/test")
