cmake_minimum_required(VERSION 3.30...4.0)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/lib/vcpkg/scripts/buildsystems/vcpkg.cmake"
	CACHE STRING "Vcpkg toolchain file" FORCE)

project(rig_gui
	LANGUAGES CXX C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Widgets QuickWidgets)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include("./cmake/cpp.cmake")
include("./cmake/qml.cmake")

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(guidev WIN32 MACOSX_BUNDLE
	${APP_SOURCES} ${WIDGET_SOURCES})

target_include_directories(guidev PRIVATE ${STD_APP_INCLUDES})
target_compile_warn_all(guidev)

target_link_libraries(guidev PRIVATE ${STD_APP_QT6_DEPS})

# Ideally you would quickly iter using the dev gui app
qt_add_qml_module(qml.a_circle
	URI qml.a_circle
	OUTPUT_DIRECTORY "qml/a_circle"
	QML_FILES
		"qml/circle.qml"
)

add_library(plotting_iface SHARED ${PLOTTING_SOURCES})
target_link_libraries(plotting_iface PRIVATE Qt6::Core Qt6::Widgets)
target_include_directories(plotting_iface PUBLIC ${PLOTTING_SRC_DIR})

target_compile_warn_all(plotting_iface)

add_subdirectory("${CMAKE_SOURCE_DIR}/lib/gr")
find_package(GR REQUIRED)

add_library(gr_backend SHARED ${GR_BKND_SOURCES})
get_target_property(QT6GR_INCLUDES GR::GR INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(gr_backend PUBLIC
	${QT6GR_INCLUDES} "${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/build/_deps/gr-src/lib/gr") #FIXME: this is really bad
target_link_libraries(gr_backend PRIVATE plotting_iface)
target_link_libraries(gr_backend PRIVATE Qt6::Core Qt6::Widgets)
target_link_libraries(gr_backend PUBLIC GR::qt6gr)

target_compile_warn_all(gr_backend)

qt_add_executable(widgets_recreation WIN32 MACOSX_BUNDLE
	"${WINDOWING_SRC_DIR}/WidgetsRecreation.cpp"
	${OTHER_APP_SOURCES} ${WIDGET_SOURCES} ${PLOTTING_SOURCES})

target_include_directories(widgets_recreation PRIVATE ${STD_APP_INCLUDES})
target_compile_warn_all(widgets_recreation)

target_link_libraries(widgets_recreation PRIVATE ${STD_APP_QT6_DEPS})
target_link_libraries(widgets_recreation PRIVATE gr_backend)
