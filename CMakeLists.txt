cmake_minimum_required(VERSION 3.15)

project(differintC VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Pybind11
include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v2.11.0
)
FetchContent_MakeAvailable(pybind11)

# Core C++ Library
add_library(differint_core src/differint.cpp)
target_include_directories(differint_core PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Add Python bindings
add_subdirectory(python)