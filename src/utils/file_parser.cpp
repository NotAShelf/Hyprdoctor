#include "file_parser.h"
#include <fstream>
#include <stdexcept>

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
