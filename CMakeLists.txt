cmake_minimum_required(VERSION 4.0)

project(rig_gui
	LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Widgets QuickWidgets)

qt_standard_project_setup(REQUIRES 6.10)

set(SOURCES
	src/main.cpp)

set(WIDGET_SOURCES
	src/MainWindow/MainWindow.cpp)

qt_add_executable(gui WIN32 MACOSX_BUNDLE ${SOURCES} ${WIDGET_SOURCES})

target_link_libraries(gui PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
	Qt6::Widgets
	Qt6::QuickWidgets
)
