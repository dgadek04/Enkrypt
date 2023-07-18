#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>

std::string readFile(const std::string& filePath);
bool writeFile(const std::string& filePath, const std::string& content);

#endif
