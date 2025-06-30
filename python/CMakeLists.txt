pybind11_add_module(differintC module.cpp ../src/differint.cpp)

target_include_directories(differintC
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(differintC
    PRIVATE differint_core
)

# Windows-specific DLL handling
if(WIN32)
    add_custom_command(TARGET differintC POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${FFTW_ROOT}/bin/libfftw3-3.dll"
            $<TARGET_FILE_DIR:differintC>
    )
endif()

set_target_properties(differintC PROPERTIES
    PREFIX ""
    SUFFIX ".pyd"
)

install(TARGETS differintC
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/Lib/site-packages)