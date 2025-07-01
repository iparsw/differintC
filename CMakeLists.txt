cmake_minimum_required(VERSION 3.15)

project(differintC VERSION 0.0.2.3 LANGUAGES CXX)

# Set compiler optimization flags
if(MSVC)
    add_compile_options(/O2 /fp:fast /arch:AVX2)
else()
    add_compile_options(-O3 -march=native -ffast-math)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Robust FFTW setup
# set(FFTW_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/fftw")
# set(FFTW_INCLUDE_DIRS "${FFTW_ROOT}/include")
#
# # Check if we're in a temporary build directory
# if(NOT EXISTS "${FFTW_ROOT}/lib/libfftw3-3.lib")
#     # Try to find FFTW in the source directory
#     set(FFTW_ROOT_SOURCE "${CMAKE_SOURCE_DIR}/thirdparty/fftw")
#     if(EXISTS "${FFTW_ROOT_SOURCE}/lib/libfftw3-3.lib")
#         set(FFTW_ROOT "${FFTW_ROOT_SOURCE}")
#         set(FFTW_INCLUDE_DIRS "${FFTW_ROOT}/include")
#         message(STATUS "Using source FFTW directory: ${FFTW_ROOT}")
#     else()
#         # Fallback to system FFTW
#         find_package(FFTW)
#         if(FFTW_FOUND)
#             message(STATUS "Using system FFTW")
#             set(FFTW_LIBRARIES ${FFTW_LIBRARIES})
#         else()
#             message(FATAL_ERROR "FFTW not found! Please install FFTW or check the thirdparty directory.")
#         endif()
#     endif()
# endif()

# Use bundled FFTW from thirdparty
set(FFTW_ROOT "${CMAKE_SOURCE_DIR}/thirdparty/fftw")
set(FFTW_INCLUDE_DIRS "${FFTW_ROOT}/include")

if(WIN32)
    set(FFTW_LIBRARIES "${FFTW_ROOT}/lib/libfftw3-3.lib")
else()
    set(FFTW_LIBRARIES "${FFTW_ROOT}/lib/libfftw3.so")
endif()

# Optional sanity check
if(NOT EXISTS "${FFTW_LIBRARIES}")
    message(FATAL_ERROR "Missing FFTW library at: ${FFTW_LIBRARIES}")
endif()
##########################################


if(WIN32)
    set(FFTW_LIBRARIES "${FFTW_ROOT}/lib/libfftw3-3.lib")
else()
    set(FFTW_LIBRARIES "${FFTW_ROOT}/lib/libfftw3.so")
endif()

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
target_include_directories(differint_core PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${FFTW_INCLUDE_DIRS}
)
target_link_libraries(differint_core PRIVATE ${FFTW_LIBRARIES})

# Add Python bindings
add_subdirectory(python)

# Mark installation component for scikit-build
install(CODE "message(STATUS \"Installing differintC component\")" COMPONENT python)