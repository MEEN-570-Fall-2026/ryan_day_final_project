file(GLOB MATERIALS_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/materials/*.cpp"
)

file(GLOB MATERIALS_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/materials/*.hpp"
)

file(GLOB LOADS_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/loads/*.cpp"
)

file(GLOB LOADS_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/loads/*.hpp"
)

file(GLOB_RECURSE CONSTRAINTS_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/constraints/*.cpp"
)

file(GLOB_RECURSE CONSTRAINTS_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/constraints/*.hpp"
)

add_library(Solvers STATIC)
target_sources(Solvers
    PRIVATE
        Solver.cpp
        StructuralSolver.cpp
        ${LOADS_SOURCES}
        ${CONSTRAINTS_SOURCES}
        ${MATERIALS_SOURCES}
    PUBLIC
        Solver.hpp
        StructuralSolver.hpp
        ${LOADS_HEADERS}
        ${CONSTRAINTS_HEADERS}
        ${MATERIALS_HEADERS}
        UnassignedMaterialException.hpp
)
target_compile_features(Solvers PRIVATE cxx_std_20)

target_link_libraries(Solvers
    PUBLIC
        Mesher
)

target_include_directories(Solvers
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)