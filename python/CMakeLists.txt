# Python bindings target
pybind11_add_module(_differintC module.cpp)  # Keep underscore prefix # REMOVED ../src/differint.cpp

target_include_directories(_differintC
    PRIVATE ${CMAKE_SOURCE_DIR}/include
    ${FFTW_INCLUDE_DIRS}
)


target_link_libraries(_differintC
    PRIVATE
        differint_core
        ${FFTW_LIBRARIES}  # ADD THIS LINE
)



# Set output name to match what Python expects
set_target_properties(_differintC PROPERTIES
    # OUTPUT_NAME "_differintC"  # Output file will be differintC.pyd (no leading underscore)
    PREFIX ""
    SUFFIX ".pyd"
)

# Windows-specific FFTW DLL handling
if(WIN32)
    # Copy DLL to module output directory for development
    add_custom_command(TARGET _differintC POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${FFTW_ROOT}/bin/libfftw3-3.dll"
            $<TARGET_FILE_DIR:_differintC>
    )

    # Also copy to main build directory for convenience
    add_custom_command(TARGET _differintC POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${FFTW_ROOT}/bin/libfftw3-3.dll"
            ${CMAKE_BINARY_DIR}
    )
endif()

# Also install the pure Python files (__init__.py and libfftw3-3.dll)
install(
    FILES
        ${CMAKE_SOURCE_DIR}/differintC/__init__.py
        ${CMAKE_SOURCE_DIR}/differintC/libfftw3-3.dll  # just for windows
    # DESTINATION Lib/site-packages/differintC
    DESTINATION differintC # Relative path only # Install directly to site-packages
    COMPONENT python
)

if(WIN32)
    install(
        FILES
            "${FFTW_ROOT}/bin/libfftw3-3.dll"
        DESTINATION differintC  # Relative path only
        COMPONENT python
    )
endif()

# Install the .pyd file directly to site-packages
install(TARGETS _differintC
    # RUNTIME DESTINATION Lib/site-packages/differintC OLD
    # LIBRARY DESTINATION Lib/site-packages/differintC OLD
    # ARCHIVE DESTINATION Lib/site-packages/differintC OLD
    RUNTIME DESTINATION differintC COMPONENT python  # Windows
    LIBRARY DESTINATION differintC COMPONENT python  # Linux/Mac
    ARCHIVE DESTINATION differintC COMPONENT python  # Static lib (not used)
)


# explicit logging to verify paths
install(CODE [[
    message(STATUS "Installing to: ${CMAKE_INSTALL_PREFIX}/differintC")
    file(GLOB_RECURSE INSTALLED_FILES LIST_DIRECTORIES false
         RELATIVE "${CMAKE_INSTALL_PREFIX}"
         "${CMAKE_INSTALL_PREFIX}/differintC/*")
    message(STATUS "Installed files: ${INSTALLED_FILES}")
]] COMPONENT python)