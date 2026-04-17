cmake_minimum_required(VERSION 4.0)
project(DVD_simulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(DVD_simulator main.cpp)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)
target_link_libraries(DVD_simulator PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)

