# OpenSSL-EVP-C++

This project demonstrates how to use the OpenSSL EVP API (`openssl/evp.h`) in C++ to implement various cryptographic techniques. It serves as an introductory guide to the powerful features provided by OpenSSL's EVP API, covering the following areas:

- **Hashing**: Securely hash data using various algorithms.
- **Key Generation**: Create cryptographic keys for signing, encryption, and decryption tasks.
- **Signing**: Use private keys to sign data for authentication purposes.
- **Verifying**: Verify signatures to ensure data integrity and authenticity.

---

## Features
- Comprehensive examples of hashing, signing, and verifying.
- Demonstrates how to handle cryptographic key generation.
- A clean and structured approach to using the EVP API in C++.

---

## Prerequisites

Ensure the following dependencies are installed:

### OpenSSL Installation

#### On Ubuntu/Debian-based Systems:
```bash
sudo apt-get install openssl
```

#### On Arch-based Systems:
```bash
sudo pacman -S openssl
```

### Development Tools
- GCC or Clang compiler
- `make` utility

---

## Getting Started

### Building the Program

1. **Clean Previous Builds**
   Remove any existing compiled files:
   ```bash
   make clean
   ```

2. **Compile the Program**
   Build the main executable:
   ```bash
   make main
   ```

3. **Run the Program**
   Execute the compiled program using:
   ```bash
   ./object/main
   ```
   Alternatively, you can use the following command:
   ```bash
   make exec
   ```

---

## Example Usage

Demonstrate cryptographic techniques like:
- Hashing a message
- Generating and saving cryptographic keys
- Signing a message with a private key
- Verifying the signature with a public key

Refer to the source code for detailed examples.

---

## License

This project is licensed under both the OpenSSL License and the Apache License 2.0. For more details, refer to the LICENSE file or the links below:

- [OpenSSL License](https://www.openssl.org/source/license.html)
- [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0)

---

## Acknowledgments

This project utilizes the OpenSSL library, an industry-standard tool for secure communication and cryptographic operations.

