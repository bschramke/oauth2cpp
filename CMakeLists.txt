cmake_minimum_required(VERSION 3.1)
project(OAuth2Cpp)

# Append our module directory to CMake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(liboauth2cpp)