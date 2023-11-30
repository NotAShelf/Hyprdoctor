
#include "src/utils/environment.h"
#include "src/utils/file_parser.h"
#include "src/utils/json_parser.h"
#include <iostream>

int main() {
  const char *envVar = getEnvVar("HYPRLAND_INSTANCE_SIGNATURE");

  // try opening the log file
  try {
    std::string filePath = "/tmp/hypr/" + std::string(envVar);
    std::vector<std::string> errLines = readErrLines(filePath);

    // associate each error with the issue ID and name
    std::vector<std::pair<int, std::string>> issues =
        findErrorsInJsonFiles(errLines, "database");

    for (const auto &[id, name] : issues) {
      std::cout << "Issue ID: " << id << ", Name: " << name << std::endl;
    }
  } catch (const std::runtime_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
