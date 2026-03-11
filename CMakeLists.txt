cmake_minimum_required(VERSION 3.30...4.0)

project(rig_gui
	LANGUAGES CXX
)

if (MSVC)
	add_compile_options("/W4")
else()
	add_compile_options("-Wall")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_AUTOMOC ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include("./cmake/cpp.cmake")
include("./cmake/qml.cmake")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Widgets QuickWidgets)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(guidev WIN32 MACOSX_BUNDLE ${APP_SOURCES} ${WIDGET_SOURCES})
target_include_directories(guidev PRIVATE
	src/Widgets)

target_link_libraries(guidev PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
	Qt6::Widgets
	Qt6::QuickWidgets
)

# Ideally you would quickly iter using the dev gui app
qt_add_qml_module(qml.a_circle
	URI qml.a_circle
	OUTPUT_DIRECTORY "qml/a_circle"
	QML_FILES
		"qml/circle.qml"
)

find_package(GR) # not required yet
if (GR_FOUND)
	target_link_libraries(guidev PUBLIC GR::qt6gr)
endif()
