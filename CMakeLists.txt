cmake_minimum_required(VERSION 3.23)

project(QtVTK LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
add_subdirectory(Interpreter)


target_compile_definitions(tests PRIVATE
    TEST_FILES_DIR="${CMAKE_CURRENT_BINARY_DIR}/SampleFiles"
)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/SampleFiles"
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
