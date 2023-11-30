#include "src/utils/environment.h"
#include "src/utils/file_parser.h"
#include "src/utils/json_parser.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  po::options_description desc("Allowed options");
  desc.add_options()("help", "Produce help message")("verbose",
                                                     "Enable verbose output");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
  }

  const char *envVar = getEnvVar("HYPRLAND_INSTANCE_SIGNATURE");

  // if --verbose flag is set, print the environment variable
  if (vm.count("verbose")) {
    std::cout << "HYPRLAND_INSTANCE_SIGNATURE: " << envVar << std::endl;
  }

  // try opening the log file
  try {
    if (envVar != nullptr) {
      std::string filePath = "/tmp/hypr/" + std::string(envVar);
      std::vector<std::string> errLines = readErrLines(filePath);

      // associate each error with the issue ID and name
      std::vector<std::pair<int, std::string>> issues =
          findErrorsInJsonFiles(errLines, "database", vm.count("verbose"));

      for (const auto &[id, name] : issues) {
        std::cout << "Issue ID: " << id << ", Name: " << name << std::endl;
      }
    }
  } catch (const std::runtime_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
