#include "decryption.h"
#include "file_utils.h"
#include <iostream>
#include <cstring>
#include <openssl/evp.h>

void decryptFile(const std::string& inputFile, const std::string& outputFile) {
    // Read the content of the input file
    std::string ciphertext = readFile(inputFile);

    // Extract the encryption key and IV from the ciphertext
    unsigned char encryptionKey[EVP_MAX_KEY_LENGTH];
    unsigned char iv[EVP_MAX_IV_LENGTH];
    std::string keyAndIV = ciphertext.substr(0, EVP_MAX_KEY_LENGTH + EVP_MAX_IV_LENGTH);
    ciphertext = ciphertext.substr(EVP_MAX_KEY_LENGTH + EVP_MAX_IV_LENGTH);
    memcpy(encryptionKey, keyAndIV.data(), EVP_MAX_KEY_LENGTH);
    memcpy(iv, keyAndIV.data() + EVP_MAX_KEY_LENGTH, EVP_MAX_IV_LENGTH);

    // Create an EVP_CIPHER_CTX for AES decryption
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, encryptionKey, iv);
    EVP_CIPHER_CTX_set_padding(ctx, 0);

    // Determine the required output buffer size for plaintext
    int outputSize = ciphertext.size() + EVP_CIPHER_CTX_block_size(ctx);
    std::string plaintext(outputSize, 0);
    int decryptedSize = 0;

    // Decrypt the ciphertext using AES in CBC mode
    EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(plaintext.data()), &decryptedSize,
                      reinterpret_cast<const unsigned char*>(ciphertext.data()), ciphertext.size());
    int finalDecryptedSize = 0;
    EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(plaintext.data()) + decryptedSize, &finalDecryptedSize);
    decryptedSize += finalDecryptedSize;

    // Clean up the EVP_CIPHER_CTX
    EVP_CIPHER_CTX_free(ctx);

    // Resize the plaintext to the actual decrypted size
    plaintext.resize(decryptedSize);

    // Write the plaintext to the output file
    bool success = writeFile(outputFile, plaintext);

    if (success) {
        std::cout << "File decrypted successfully.\n";
    } else {
        std::cerr << "Error writing decrypted file.\n";
    }
}

#include "decryption.h"

int main() {
    std::string inputFile = "input.txt";
    std::string outputFile = "output.txt";

    decryptFile(inputFile, outputFile);

    return 0;
}
