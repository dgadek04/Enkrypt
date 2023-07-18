#include "encryption.h"
#include "file_utils.h"
#include <iostream>
#include <openssl/aes.h>

void encryptFile(const std::string& inputFile, const std::string& outputFile) {
    // Read the content of the input file
    std::string plaintext = readFile(inputFile);

    // Generate a random encryption key (128 bits for AES-128)
    unsigned char encryptionKey[AES_BLOCK_SIZE];
    // ... generate the key here

    // Generate initialization vector (IV) for AES encryption
    unsigned char iv[AES_BLOCK_SIZE];
    // ... generate the IV here

    // Perform AES encryption
    AES_KEY aesKey;
    AES_set_encrypt_key(encryptionKey, 128, &aesKey);
    
    // Determine the required output buffer size for ciphertext
    int outputSize = ((plaintext.size() + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    std::string ciphertext(outputSize, 0);
    
    // Encrypt the plaintext using AES in CBC mode
    AES_cbc_encrypt(reinterpret_cast<const unsigned char*>(plaintext.data()),
                    reinterpret_cast<unsigned char*>(ciphertext.data()),
                    plaintext.size(),
                    &aesKey,
                    iv,
                    AES_ENCRYPT);
    
    // Write the ciphertext to the output file
    writeFile(outputFile, ciphertext);
}
