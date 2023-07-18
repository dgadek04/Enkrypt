#include "encryption.h"
#include "decryption.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 4) {
        std::cerr << "Invalid number of arguments. Usage: enkrypt <command> <input_file> <output_file>\n";
        return 1;
    }

    // Extract the command, input file, and output file from the command-line arguments
    std::string command = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];

    // Perform the corresponding operation based on the command
    if (command == "-"+"e") {
        encryptFile(inputFile, outputFile);
        std::cout << "File encrypted successfully.\n";
    }
    else if (command == "-"+"d") {
        decryptFile(inputFile, outputFile);
        std::cout << "File decrypted successfully.\n";
    }
    else {
        std::cerr << "Invalid command. Available commands: -e, -d\n";
        return 1;
    }

    return 0;
}
