file(GLOB PRIMITIVES3D_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/primitives3d/*.cpp"
)

file(GLOB PRIMITIVES3D_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/primitives3d/*.hpp"
)

add_library(Modeler STATIC)
target_sources(Modeler
    PRIVATE
        Modeler.cpp
        Point.cpp
        SurfaceTriangle.cpp
        ${PRIMITIVES3D_SOURCES}
    PUBLIC
        Modeler.hpp
        Point.hpp
        SurfaceTriangle.hpp
        ${PRIMITIVES3D_HEADERS}
)
target_compile_features(Modeler PRIVATE cxx_std_20)

target_include_directories(Modeler
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)