#include "file_utils.h"
#include <fstream>
#include <iostream>

std::string readFile(const std::string& filePath) {
    std::ifstream inputFile(filePath);
    if (!inputFile) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    return content;
}

bool writeFile(const std::string& filePath, const std::string& content) {
    std::ofstream outputFile(filePath);
    if (!outputFile) {
        std::cerr << "Error creating file: " << filePath << std::endl;
        return false;
    }

    outputFile << content;
    outputFile.close();

    return true;
}
