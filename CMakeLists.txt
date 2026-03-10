cmake_minimum_required(VERSION 3.30)

project(rig_gui
	LANGUAGES CXX
)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Widgets QuickWidgets)

qt_standard_project_setup(REQUIRES 6.10)

if (MSVC)
	add_compile_options("/W4")
else()
	add_compile_options("-Wall")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_AUTOMOC ON)

set(SOURCES
	src/main.cpp)

set(WIDGET_SOURCES
	src/Windowing/DevWindow.cpp
	src/Windowing/NumericTestWidget.cpp
	src/Widgets/Dial/AttitudeDial.cpp)

qt_add_executable(guidev WIN32 MACOSX_BUNDLE ${SOURCES} ${WIDGET_SOURCES})

target_link_libraries(guidev PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
	Qt6::Widgets
	Qt6::QuickWidgets
)

target_include_directories(guidev PRIVATE
	src/Widgets)
