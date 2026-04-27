#
#	This file is for:
#	- Encapsulating some platform and compiler differences
#	- Source declaration
#	- Qt6 dependency declaration
#

set(WINDOWING_SRC_DIR "${CMAKE_SOURCE_DIR}/src/Windowing")
set(WIDGETS_SRC_DIR "${CMAKE_SOURCE_DIR}/src/Widgets")
set(PLOTTING_SRC_DIR "${CMAKE_SOURCE_DIR}/src/Plotting")
set(UTIL_SRC_DIR "${CMAKE_SOURCE_DIR}/src/Util")

set(APP_SOURCES
	"${CMAKE_SOURCE_DIR}/src/Main.cpp"
	"${WINDOWING_SRC_DIR}/MainWindow.cpp")

set(DIAL_SOURCES
	"${WIDGETS_SRC_DIR}/Dial/Attitude.cpp"
	"${WIDGETS_SRC_DIR}/Dial/Composite.cpp")

set(DISPLAYER_SOURCES
	"${WIDGETS_SRC_DIR}/Displays/RateLabel.cpp"
	"${WIDGETS_SRC_DIR}/Displays/MultiPlotContainer.cpp"
	"${WIDGETS_SRC_DIR}/Displays/StatusCollector.cpp")

set(WIDGET_SOURCES
	${WINDOWING_SOURCES}
	${DIAL_SOURCES}
	${DISPLAYER_SOURCES})

set(PLOTTING_SOURCES
	"${PLOTTING_SRC_DIR}/Plot2D.cpp")

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
