cmake_minimum_required(VERSION 3.26)
project(Engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(Source)
add_subdirectory(Test)

option(BUILD_EXAMPLES "Build example applications" ON)
if(BUILD_EXAMPLES)
  add_subdirectory(Examples/HelloWorld)
endif()
