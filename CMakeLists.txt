
# You are free to modify this file

cmake_minimum_required(VERSION 3.0)
project(game)
find_package(X11 REQUIRED)

set (CMAKE_BUILD_DIRECTORY "${dir}/build")
set (CMAKE_BINARY_DIR "${dir}/bin")
set (CMAKE_CONFIGURATION_TYPES "Debug" "Release")

if (APPLE)
    set (CMAKE_CXX_COMPILER "/Library/Developer/CommandLineTools/usr/bin/c++")
    set (CMAKE_C_COMPILER "/Library/Developer/CommandLineTools/usr/bin/cc")
    set (CMAKE_CXX_FLAGS "-I/usr/local/include/")

    link_directories(/usr/local/Cellar/libx11/1.8.1/lib)
endif()

file(GLOB SRC *.cpp)
add_executable(game ${SRC})
set_property(TARGET game PROPERTY CXX_STANDARD 17)
target_link_libraries(game X11)
