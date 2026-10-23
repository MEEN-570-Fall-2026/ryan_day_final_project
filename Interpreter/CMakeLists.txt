
add_library(Interpreter STATIC)
target_sources(Interpreter
    PRIVATE
        interpreter.cpp
    PUBLIC
        interpreter.cpp
)
target_compile_features(Interpreter PRIVATE cxx_std_20)

target_include_directories(Interpreter
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)