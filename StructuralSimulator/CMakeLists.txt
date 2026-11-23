add_library(StructuralSimulator STATIC)
target_sources(StructuralSimulator
    PRIVATE
        StructuralSimulator.cpp
        PointLoad.cpp
        Constraint.cpp
    PUBLIC
        StructuralSimulator.hpp
        PointLoad.hpp
        Constraint.hpp
)
target_compile_features(StructuralSimulator PRIVATE cxx_std_20)

target_link_libraries(StructuralSimulator
    PUBLIC
        Mesher
)

target_include_directories(StructuralSimulator
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)