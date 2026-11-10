add_library(Mesher STATIC)
target_sources(Mesher
    PRIVATE
        Mesher.cpp
        Mesh.cpp
    PUBLIC
        Mesher.hpp
        Mesh.hpp
)
target_compile_features(Mesher PRIVATE cxx_std_20)

target_link_libraries(Mesher
    PUBLIC
        Modeler
)

target_include_directories(Mesher
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)