cmake_minimum_required(VERSION 3.19)
project(DVD-simulator LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools UiTools Charts)

qt_standard_project_setup()
add_compile_definitions(QT_NO_DEBUG_OUTPUT)

qt_add_executable(DVD-simulator main.cpp
        App.cpp
        App.h
        CustomWindow.cpp
        CustomWindow.h
        Canvas.cpp
        Canvas.h
        DVD.cpp
        DVD.h
        StatsTracker.cpp
        StatsTracker.h
        Standard_DVD.cpp
        Standard_DVD.h)

target_link_libraries(DVD-simulator
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::UiTools
        Qt::Charts
)

install(TARGETS DVD-simulator
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET DVD-simulator
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
