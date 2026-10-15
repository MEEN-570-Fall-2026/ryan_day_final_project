add_library(StructuralSimulator STATIC)
target_sources(StructuralSimulator
    PRIVATE
        StructuralSimulator.cpp
    PUBLIC
        StructuralSimulator.hpp
)
target_compile_features(StructuralSimulator PRIVATE cxx_std_20)

target_include_directories(StructuralSimulator
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)