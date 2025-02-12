#include "file_utils.h"
#include <iostream>
#include "cryptlib.h"
#include <aes.h>
#include <modes.h>
#include <filters.h>
#include <hex.h>

using namespace CryptoPP;

void encryptFile(const std::string& inputFile, const std::string& outputFile) {
    // Read the content of the input file
    std::string plaintext = readFile(inputFile);

    // Encryption key and IV (AES-128, 16 bytes key)
    byte encryptionKey[16] = {0x00};  // Replace with your 128-bit key (16 bytes)
    byte iv[16] = {0x00};  // Replace with your IV

    // AES encryption in CBC mode
    CBC_Mode<AES>::Encryption cbcEncryption(encryptionKey, AES::DEFAULT_KEYLENGTH, iv);  // Pass key and IV directly

    std::string ciphertext;
    StringSource(plaintext, true, 
        new StreamTransformationFilter(cbcEncryption, new StringSink(ciphertext))
    );

    // Write the ciphertext to the output file
    bool success = writeFile(outputFile, ciphertext);
    if (success) {
        std::cout << "File encrypted successfully.\n";
    } else {
        std::cerr << "Error writing encrypted file.\n";
    }
}
