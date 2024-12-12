#pragma once
#include <stdexcept>
#include<iostream>
using namespace std;
class CustomException : public exception {
private:
    const char* errorMessage;

public:
    CustomException(const char* message) : errorMessage(message) {}
    const char* what() const noexcept override;
};;

