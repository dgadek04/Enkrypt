#include "file_utils.h"
#include <iostream>
#include "cryptlib.h"
#include <aes.h>
#include <modes.h>
#include <filters.h>
#include <hex.h>

using namespace CryptoPP;

void decryptFile(const std::string& inputFile, const std::string& outputFile) {
    // Read the content of the encrypted input file
    std::string ciphertext = readFile(inputFile);

    // Encryption key and IV (AES-128, 16 bytes key)
    byte encryptionKey[16] = {0x00};  // Replace with your 128-bit key (16 bytes)
    byte iv[16] = {0x00};  // Replace with your IV

    // AES decryption in CBC mode
    CBC_Mode<AES>::Decryption cbcDecryption(encryptionKey, AES::DEFAULT_KEYLENGTH, iv);  // Pass key and IV directly

    std::string plaintext;
    StringSource(ciphertext, true, 
        new StreamTransformationFilter(cbcDecryption, new StringSink(plaintext))
    );

    // Write the decrypted plaintext to the output file
    bool success = writeFile(outputFile, plaintext);
    if (success) {
        std::cout << "File decrypted successfully.\n";
    } else {
        std::cerr << "Error writing decrypted file.\n";
    }
}
