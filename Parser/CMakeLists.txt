file(GLOB PARSETOKENS_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/parseTokens/*.cpp"
)

file(GLOB PARSETOKENS_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/parseTokens/*.hpp"
)

add_library(Parser STATIC)
target_sources(Parser
    PRIVATE
        Parser.cpp
        ParseTree.cpp
        ParseNode.cpp
        ${PARSETOKENS_SOURCES}
    PUBLIC
        Parser.hpp
        ParseTree.hpp
        ParseNode.hpp
        ${PARSETOKENS_HEADERS}
)
target_compile_features(Parser PRIVATE cxx_std_20)

target_include_directories(Parser
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)