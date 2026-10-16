add_library(Modeler STATIC)
target_sources(Modeler
    PRIVATE
        Modeler.cpp
        Point.cpp
    PUBLIC
        Modeler.hpp
        Point.hpp
)
target_compile_features(Modeler PRIVATE cxx_std_20)

target_include_directories(Modeler
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)