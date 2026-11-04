add_library(Exceptions INTERFACE)

target_sources(Exceptions
    INTERFACE
        InterpreterException.hpp
        ContextException.hpp
)

target_compile_features(Exceptions INTERFACE cxx_std_20)

target_include_directories(Exceptions
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)