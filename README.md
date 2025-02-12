# Enkrypt

**Enkrypt** is a command-line file encryption and decryption tool implemented in **C++**. It provides a simple and secure way to protect sensitive files by encrypting them using symmetric key encryption algorithms like **AES**.

## Features
- **Command-line Interface (CLI)** for easy use and integration.
- Uses **AES** encryption (AES-128, 16 bytes key) in **CBC mode** to ensure high security.
- Allows both **file encryption** and **decryption**.
- Cross-platform support with **Crypto++** library.
  
## Requirements
- **C++11** or higher.
- **Crypto++** library installed (for AES encryption/decryption).
- Compiler with support for C++ (GCC or MinGW recommended for Windows).

## How to Use

### Encryption
To encrypt a file, use the following command:
```bash
./encryption.exe input.txt output.enc
