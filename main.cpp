#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// value of an environment variable
const char *getEnvVar(const char *name) {
  const char *value = std::getenv(name);
  if (value == nullptr) {
    throw std::runtime_error(std::string("Environment variable ") + name +
                             " is not set.");
  }

  return value;
}

// print the value of an environment variable
void printEnvVar(const char *name) {
  const char *value = getEnvVar(name);
  std::cout << name << "=" << value << std::endl;
}

// read the logs and return the lines that start with [ERR]
// which are standard errors
std::vector<std::string> readErrLines(const std::string &filePath) {
  std::ifstream file(filePath);
  if (!file.is_open()) {
    throw std::runtime_error("Unable to open file at " + filePath);
  }

  std::string line;
  std::vector<std::string> errLines;

  while (std::getline(file, line)) {
    if (line.substr(0, 5) == "[ERR]") {
      errLines.push_back(line);
    }
  }

  file.close();
  return errLines;
}

int main() {
  const char *envVar = getEnvVar("HYPRLAND_INSTANCE_SIGNATURE");
  std::cout << "Variable HYPRLAND_INSTANCE_SIGNATURE is set to " << envVar
            << std::endl;

  try {
    std::string filePath = "/tmp/hypr/" + std::string(envVar);
    std::vector<std::string> errLines = readErrLines(filePath);

    // print error lines
    for (const auto &line : errLines) {
      std::cout << line << std::endl;
    }
  } catch (const std::runtime_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
