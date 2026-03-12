set(WINDOWING_SRC_DIR "${CMAKE_SOURCE_DIR}/src/Windowing")
set(WIDGETS_SRC_DIR "${CMAKE_SOURCE_DIR}/src/Widgets")
set(PLOTTING_SRC_DIR "${CMAKE_SOURCE_DIR}/src/Plotting")

set(APP_SOURCES
	src/main.cpp)

set(WIDGET_SOURCES
	"${WINDOWING_SRC_DIR}/DevWindow.cpp"
	"${WINDOWING_SRC_DIR}/WidgetsRecreation.cpp"
	"${WINDOWING_SRC_DIR}/NumericTestWidget.cpp"
	"${WIDGETS_SRC_DIR}/Dial/AttitudeDial.cpp")

set(PLOTTING_SOURCES
	"${PLOTTING_SRC_DIR}/Plot2D.cpp"
	"${PLOTTING_SRC_DIR}/Container.cpp"
	"${PLOTTING_SRC_DIR}/Backend/GR.cpp")

set(STD_APP_INCLUDES
	"${CMAKE_SOURCE_DIR}/src"
	${WIDGETS_SRC_DIR})
