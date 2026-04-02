cmake_minimum_required(VERSION 3.30...4.0)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/lib/vcpkg/scripts/buildsystems/vcpkg.cmake"
	CACHE STRING "Vcpkg toolchain file" FORCE)

project(rig_gui
	LANGUAGES CXX C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_AUTOMOC ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Widgets QuickWidgets Charts)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include("./cmake/cpp.cmake")
include("./cmake/qml.cmake")

qt_standard_project_setup(REQUIRES 6.10)

#qt_add_executable(guidev WIN32 MACOSX_BUNDLE
#	${APP_SOURCES} ${WIDGET_SOURCES})
#
#target_include_directories(guidev PRIVATE ${STD_APP_INCLUDES})
#target_compile_warn_all(guidev)
#
#target_link_libraries(guidev PRIVATE ${STD_APP_QT6_DEPS})

# Plotting Interface
add_library(plotting_iface SHARED ${PLOTTING_SOURCES})
target_link_libraries(plotting_iface PUBLIC Qt6::Core Qt6::Widgets)
target_include_directories(plotting_iface PUBLIC ${PLOTTING_SRC_DIR})
target_compile_definitions(plotting_iface PRIVATE COMPILING_PLOT_API_DLL)
target_compile_warn_all(plotting_iface)

# QChart Backend Compilation
add_library(qchart_backend SHARED ${QCHART_BKND_SOURCES})
target_include_directories(qchart_backend PUBLIC "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(qchart_backend PUBLIC plotting_iface)
target_link_libraries(qchart_backend PUBLIC Qt6::Core Qt6::Widgets Qt6::Charts)
target_compile_definitions(qchart_backend PRIVATE COMPILING_QCHART_BACKEND_DLL)
target_compile_warn_all(qchart_backend)


# Widgets Recreation
qt_add_executable(widgets_recreation WIN32 MACOSX_BUNDLE
	"${WINDOWING_SRC_DIR}/WidgetsRecreation.cpp"
	${OTHER_APP_SOURCES} ${WIDGET_SOURCES}) # ${PLOTTING_SOURCES}

target_include_directories(widgets_recreation PRIVATE ${STD_APP_INCLUDES})
target_compile_warn_all(widgets_recreation)

target_link_libraries(widgets_recreation PRIVATE ${STD_APP_QT6_DEPS})
target_link_libraries(widgets_recreation PRIVATE qchart_backend)
