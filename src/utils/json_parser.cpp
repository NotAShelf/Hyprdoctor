#include "json_parser.h"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

std::vector<std::pair<int, std::string>>
findErrorsInJsonFiles(const std::vector<std::string> &errLines,
                    const std::string &dirPath, bool verbose) {
 std::vector<std::pair<int, std::string>> issues;

 for (const auto &entry : std::filesystem::directory_iterator(dirPath)) {
   if (verbose) {
     std::cout << "Processing file: " << entry.path() << std::endl;
   }
   std::ifstream file(entry.path());
   nlohmann::json j;
   file >> j;

   if (j.contains("errors") && j["errors"].is_array()) {
     for (const auto &error : j["errors"]) {
       if (std::find(errLines.begin(), errLines.end(), error) !=
           errLines.end()) {
         issues.push_back({j["ID"], j["name"]});
         break;
       }
     }
   } else {
     throw std::runtime_error("Invalid JSON file");
   }
 }

 return issues;
}
