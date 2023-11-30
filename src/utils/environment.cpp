#include "environment.h"
#include <cstdlib>
#include <iostream>

const char* getEnvVar(const char* name) {
    const char* value = std::getenv(name);
    if (value == nullptr) {
        throw std::runtime_error(std::string("Environment variable ") + name + " is not set.");
    }
    return value;
}

void printEnvVar(const char* name) {
    const char* value = getEnvVar(name);
    std::cout << name << "=" << value << std::endl;
}
