#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<int, std::string>>
findErrorsInJsonFiles(const std::vector<std::string> &errLines,
                      const std::string &dirPath, bool verbose);

#endif
