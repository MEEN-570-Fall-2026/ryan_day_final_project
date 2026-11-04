#ifndef INTERPRETEREXCEPTION
#define INTERPRETEREXCEPTION

#include <iostream>
#include <exception>
#include <string>

class InterpreterException : public std::exception {
    public:
        InterpreterException(const std::string& argument, std::string unknownToken) {
            message = "Error while interpreting argument '" + argument + "' (Unknown token: " + unknownToken + ")";
        }

        const char* what() const noexcept override {
            return message.c_str();
        }
    
    private:
        std::string message;
};

#endif