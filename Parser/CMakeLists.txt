add_library(Parser STATIC)
target_sources(Parser
    PRIVATE
        Parser.cpp
    PUBLIC
        Parser.hpp
)
target_compile_features(Parser PRIVATE cxx_std_20)

target_include_directories(Parser
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        Commands
)