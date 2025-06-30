cmake_minimum_required(VERSION 3.15)

project(differintC VERSION 0.1 LANGUAGES CXX)

# Set compiler optimization flags
if(MSVC)
    add_compile_options(/O2 /fp:fast /arch:AVX2)
else()
    add_compile_options(-O3 -march=native -ffast-math)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows-specific FFTW setup
if(WIN32)
    set(FFTW_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/fftw)
    set(FFTW_INCLUDE_DIRS ${FFTW_ROOT}/include)
    set(FFTW_LIBRARIES ${FFTW_ROOT}/lib/libfftw3-3.lib)

    # Copy DLL to output directory
    file(COPY ${FFTW_ROOT}/bin/libfftw3-3.dll
         DESTINATION ${CMAKE_BINARY_DIR}
    )
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