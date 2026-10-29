
add_library(Interpreter STATIC)
target_sources(Interpreter
    PRIVATE
        Interpreter.cpp
    PUBLIC
        Interpreter.hpp
)
target_compile_features(Interpreter PRIVATE cxx_std_20)

target_include_directories(Interpreter
    PUBLIC
        Parser
        Modeler
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Interpreter
    Parser
    Modeler
)