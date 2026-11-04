#ifndef CONTEXTEXCEPTION
#define CONTEXTEXCEPTION

#include <iostream>
#include <exception>
#include <string>

class ContextException : public std::exception {
    public:
        ContextException(const std::string& variable) {
            message = "Unrecognized variable '" + variable + "'";
        }

        const char* what() const noexcept override {
            return message.c_str();
        }
    
    private:
        std::string message;
};

#endif