cmake_minimum_required(VERSION 3.30...4.0)

project(rig_gui
	LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_AUTOMOC ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include("./cmake/cpp.cmake")
include("./cmake/qml.cmake")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Widgets QuickWidgets)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(guidev WIN32 MACOSX_BUNDLE
	${APP_SOURCES} ${WIDGET_SOURCES})

target_include_directories(guidev PRIVATE ${STD_APP_INCLUDES})
target_compile_warn(guidev)

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

if (WIN32)
	message("-- GR backend will not build on Windows.")

else()
	add_library(plotting_iface SHARED ${PLOTTING_SOURCES})
	target_link_libraries(plotting_iface PRIVATE Qt6::Core Qt6::Widgets)
	target_include_directories(plotting_iface PUBLIC ${PLOTTING_SRC_DIR})

	target_compile_warn(plotting_iface)

	find_package(GR REQUIRED) # not required yet
	message("-- Will build GR backend.")

	add_library(gr_backend SHARED ${GR_BKND_SOURCES})
	target_include_directories(gr_backend PUBLIC "${CMAKE_SOURCE_DIR}/src")
	target_link_libraries(gr_backend PRIVATE plotting_iface)
	target_link_libraries(gr_backend PRIVATE Qt6::Core Qt6::Widgets)
	target_link_libraries(gr_backend PRIVATE GR::qt6gr)

	target_compile_warn(gr_backend)

	qt_add_executable(widgets_recreation WIN32 MACOSX_BUNDLE
		"${WINDOWING_SRC_DIR}/WidgetsRecreation.cpp"
		${OTHER_APP_SOURCES} ${WIDGET_SOURCES} ${PLOTTING_SOURCES})

	target_include_directories(widgets_recreation PRIVATE ${STD_APP_INCLUDES})
	target_compile_warn(widgets_recreation)

	target_link_libraries(widgets_recreation PRIVATE
		Qt6::Core
		Qt6::Gui
		Qt6::Qml
		Qt6::Quick
		Qt6::Widgets
		Qt6::QuickWidgets
	)

	target_link_libraries(widgets_recreation PRIVATE gr_backend)

endif() # WIN32
