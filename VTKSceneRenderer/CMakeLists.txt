add_library(VTKSceneRenderer STATIC)
target_sources(VTKSceneRenderer
    PRIVATE
        VtkSceneRenderer.cpp
    PUBLIC
        VtkSceneRenderer.hpp
)
target_compile_features(VTKSceneRenderer PRIVATE cxx_std_20)

target_include_directories(VTKSceneRenderer
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)