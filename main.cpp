#include "src/utils/environment.h"
#include "src/utils/file_parser.h"
#include <iostream>

int main() {
  const char *envVar = getEnvVar("PATH");

  // try opening the log file
  try {
    std::string filePath = "/tmp/hypr/" + std::string(envVar);
    std::vector<std::string> errLines = readErrLines(filePath);

    // print [ERR] lines, which are caught errors that we prioritize
    for (const auto &line : errLines) {
      std::cout << line << std::endl;
    }
  } catch (const std::runtime_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
