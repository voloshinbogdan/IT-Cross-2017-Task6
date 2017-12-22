cmake_minimum_required(VERSION 2.8.11)

project(Weather)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(
	Weather
	main.cpp)

target_link_libraries(Weather Qt5::Widgets)
target_link_libraries(Weather Qt5Network)
