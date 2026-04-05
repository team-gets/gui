# Plotting Interface
add_library(plot_widget SHARED ${PLOTTING_SOURCES})
target_link_libraries(plot_widget PUBLIC Qt6::Core Qt6::Widgets)
target_include_directories(plot_widget PUBLIC ${PLOTTING_SRC_DIR})
target_compile_definitions(plot_widget PRIVATE COMPILING_PLOT_API_DLL)
target_compile_warn_all(plot_widget)

# QChart Backend Compilation
add_library(plot_widget_qchart SHARED ${QCHART_BKND_SOURCES})
target_include_directories(plot_widget_qchart PUBLIC "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(plot_widget_qchart PUBLIC plot_widget)
target_link_libraries(plot_widget_qchart PUBLIC Qt6::Core Qt6::Widgets Qt6::Charts)
target_compile_definitions(plot_widget_qchart PRIVATE COMPILING_QCHART_BACKEND_DLL)
target_compile_warn_all(plot_widget_qchart)

add_library(VSCL::Plot ALIAS plot_widget)
add_library(VSCL::Plot::QChart ALIAS plot_widget_qchart)
