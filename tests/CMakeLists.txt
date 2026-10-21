include(GoogleTest)

add_executable(
    tests
    Modeler_unittests.cpp
    Parser_unittests.cpp
)
target_sources(tests
    PRIVATE
        Modeler_unittests.cpp
        Parser_unittests.cpp
)
target_compile_features(tests PRIVATE cxx_std_20)
target_include_directories(tests
    PRIVATE
        "${GTEST_INCLUDE_DIRS}"
        Modeler
        Parser
)
target_link_libraries(tests
    GTest::gtest_main
    Modeler
    Parser
)

gtest_discover_tests(tests)

