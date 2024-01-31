#pragma once
#include <stdexcept>
class CustomException : public std::exception {
private:
    const char* errorMessage;

public:
    CustomException(const char* message) : errorMessage(message) {}
    const char* what() const noexcept override {
        return errorMessage;
    }
};;

