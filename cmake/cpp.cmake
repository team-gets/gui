#
#	This file is for:
#	- Encapsulating some platform and compiler differences
#	- Source declaration
#	- Qt6 dependency declaration
#

set(WINDOWING_SRC_DIR "${CMAKE_SOURCE_DIR}/src/Windowing")
set(WIDGETS_SRC_DIR "${CMAKE_SOURCE_DIR}/src/Widgets")
set(PLOTTING_SRC_DIR "${CMAKE_SOURCE_DIR}/src/Plotting")

set(APP_SOURCES
	"${CMAKE_SOURCE_DIR}/src/App/Main.cpp")

# sorry
set(OTHER_APP_SOURCES
	"${CMAKE_SOURCE_DIR}/src/App/Recreation.cpp")

set(WINDOWING_SOURCES
	"${WINDOWING_SRC_DIR}/DevWindow.cpp"
	"${WINDOWING_SRC_DIR}/NumericTestWidget.cpp")

set(DIAL_SOURCES
	"${WIDGETS_SRC_DIR}/Dial/Attitude.cpp"
	"${WIDGETS_SRC_DIR}/Dial/Composite.cpp")

set(DISPLAYER_SOURCES
	"${WIDGETS_SRC_DIR}/Displays/QuantitiesRatesDisplay.cpp"
	"${WIDGETS_SRC_DIR}/Displays/QuantitiesRatesRow.cpp"
	"${WIDGETS_SRC_DIR}/Displays/RateLabel.hpp")

set(WIDGET_SOURCES
	${WINDOWING_SOURCES}
	${DIAL_SOURCES}
	${DISPLAYER_SOURCES})

set(PLOTTING_SOURCES
	"${PLOTTING_SRC_DIR}/Plot2D.cpp"
	"${PLOTTING_SRC_DIR}/Container.cpp")

set(GR_BKND_SOURCES
	"${PLOTTING_SRC_DIR}/Backend/CoreGR.cpp")

set(QCHART_BKND_SOURCES
	"${PLOTTING_SRC_DIR}/Backend/CoreQChart.cpp")

set(STD_APP_INCLUDES
	"${CMAKE_SOURCE_DIR}/src"
	${WIDGETS_SRC_DIR})

set(STD_APP_QT6_DEPS
	Qt6::Core
	Qt6::Gui
	Qt6::Qml
	Qt6::Quick
	Qt6::Widgets
	Qt6::QuickWidgets)

function(target_compile_warn_all IN_TARGET_NAME)
	if (MSVC)
		target_compile_options(${IN_TARGET_NAME} PRIVATE "/W4")
	else()
		target_compile_options(${IN_TARGET_NAME} PRIVATE "-Wall")
	endif()
endfunction(target_compile_warn_all)

function(add_subdirectory_silence_warnings IN_DIRECTORY)
	get_directory_property(oldCompileOpts COMPILE_OPTIONS)

	if (MSVC)
		add_compile_options("/W0")
	else()
		add_compile_options("-w")
	endif()
	add_subdirectory("${IN_DIRECTORY}" EXCLUDE_FROM_ALL)

	set_directory_properties(PROPERTIES COMPILE_OPTIONS "${oldCompileOpts}")
endfunction(set_directory_compile_silence_warnings)
