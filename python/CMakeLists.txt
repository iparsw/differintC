pybind11_add_module(differintC module.cpp ../src/differint.cpp)

target_include_directories(differintC
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(differintC
    PRIVATE differint_core
)

set_target_properties(differintC PROPERTIES
    PREFIX ""
    SUFFIX ".pyd"
)

install(TARGETS differintC
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/Lib/site-packages)