cmake_minimum_required(VERSION 3.19)
project(DVD-simulator LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(DVD-simulator
    WIN32 MACOSX_BUNDLE
    main.cpp
)

target_link_libraries(DVD-simulator
    PRIVATE
        Qt::Core
        Qt::Widgets
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
