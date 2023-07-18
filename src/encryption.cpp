#include "encryption.h"
#include "file_utils.h"
#include <iostream>
#include <cstring>
#include <openssl/aes.h>
#include <openssl/rand.h>

void encryptFile(const std::string& inputFile, const std::string& outputFile) {
    // Read the content of the input file
    std::string plaintext = readFile(inputFile);

    // Generate a random encryption key (128 bits for AES-128)
    unsigned char encryptionKey[AES_BLOCK_SIZE];
    RAND_bytes(encryptionKey, AES_BLOCK_SIZE);

    // Generate initialization vector (IV) for AES encryption
    unsigned char iv[AES_BLOCK_SIZE];
    RAND_bytes(iv, AES_BLOCK_SIZE);

    // Create an AES encryption context
    AES_KEY aesKey;
    AES_set_encrypt_key(encryptionKey, 128, &aesKey);

    // Determine the required output buffer size for ciphertext
    int outputSize = plaintext.size() + AES_BLOCK_SIZE;
    std::string ciphertext(outputSize, 0);
    unsigned char* ciphertextBuffer = reinterpret_cast<unsigned char*>(ciphertext.data());

    // Encrypt the plaintext using AES in CBC mode
    AES_cbc_encrypt(reinterpret_cast<const unsigned char*>(plaintext.data()),
                    ciphertextBuffer,
                    plaintext.size(),
                    &aesKey,
                    iv,
                    AES_ENCRYPT);

    // Write the encryption key, IV, and ciphertext to the output file
    std::string keyAndIV(reinterpret_cast<const char*>(encryptionKey), AES_BLOCK_SIZE);
    keyAndIV += reinterpret_cast<const char*>(iv);
    std::string outputContent = keyAndIV + ciphertext;
    bool success = writeFile(outputFile, outputContent);

    if (success) {
        std::cout << "File encrypted successfully.\n";
    } else {
        std::cerr << "Error writing encrypted file.\n";
    }
}
