cmake_minimum_required(VERSION 3.23)

project(QtVTK LANGUAGES CXX VERSION 1.0.0)

# ----------------------------
# GoogleTest
# ----------------------------

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Required for Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# ----------------------------

include(CTest)

add_subdirectory(application)
add_subdirectory(tests)
add_subdirectory(Parser)
add_subdirectory(Modeler)
add_subdirectory(Mesher)
add_subdirectory(StructuralSimulator)
add_subdirectory(VTKSceneRenderer)
