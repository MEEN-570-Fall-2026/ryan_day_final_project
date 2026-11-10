
add_library(Interpreter STATIC)
target_sources(Interpreter
    PRIVATE
        Interpreter.cpp
        Context.cpp
        RuntimeValue.cpp
        ObjectFactory.cpp
        ObjectRegistration.cpp
        ViewerAPI.cpp
    PUBLIC
        Interpreter.hpp
        Context.hpp
        RuntimeValue.hpp
        ObjectFactory.hpp
        ObjectRegistration.hpp
        ViewerAPI.hpp
)
target_compile_features(Interpreter PRIVATE cxx_std_20)

target_include_directories(Interpreter
    PUBLIC
        Parser
        Modeler
        Exceptions
        Mesher
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Interpreter
    Parser
    Modeler
    Exceptions
    Mesher
)