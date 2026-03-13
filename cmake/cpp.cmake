set(WINDOWING_SRC_DIR "${CMAKE_SOURCE_DIR}/src/Windowing")
set(WIDGETS_SRC_DIR "${CMAKE_SOURCE_DIR}/src/Widgets")
set(PLOTTING_SRC_DIR "${CMAKE_SOURCE_DIR}/src/Plotting")

set(APP_SOURCES
	"${CMAKE_SOURCE_DIR}/src/main.cpp")

# sorry
set(OTHER_APP_SOURCES
	"${CMAKE_SOURCE_DIR}/src/recreation.cpp")

set(WIDGET_SOURCES
	"${WINDOWING_SRC_DIR}/DevWindow.cpp"
	"${WINDOWING_SRC_DIR}/NumericTestWidget.cpp"
	"${WIDGETS_SRC_DIR}/Dial/AttitudeDial.cpp")

set(PLOTTING_SOURCES
	"${PLOTTING_SRC_DIR}/Plot2D.cpp"
	"${PLOTTING_SRC_DIR}/Container.cpp")

set(GR_BKND_SOURCES
	"${PLOTTING_SRC_DIR}/Backend/GR.cpp")

set(STD_APP_INCLUDES
	"${CMAKE_SOURCE_DIR}/src"
	${WIDGETS_SRC_DIR})

function(target_compile_warn IN_TARGET_NAME)
	if (MSVC)
		target_compile_options(${IN_TARGET_NAME} PRIVATE "/W4")
	else()
		target_compile_options(${IN_TARGET_NAME} PRIVATE "-Wall")
	endif()
endfunction(target_compile_warn)
