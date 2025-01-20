# openssl-evp-cpp

This is a introduction project showcasing how to use the OpenSSL EVP API (openssl/evp.h) for implementing various cryptographic techniques using c++. The project focuses on utilizing the API for:

    Hashing: Securely hashing data with various algorithms.
    Generating Keys: Creating cryptographic keys for signing, encryption, and decryption tasks.
    Signing: Using private keys to sign data for authentication.
    Verifying: Verifying signatures to ensure data integrity and authenticity.

This project serves as an introduction to the powerful cryptographic features provided by OpenSSL’s EVP API.

---

## Prerequisites

Before running the program, ensure you have the following dependencies installed:

### Install OpenSSL:

#### On Ubuntu/Debian-based systems:

    sudo apt-get install openssl

#### On Arch-based systems:

    sudo pacman -S openssl

## Execution

#### Building the Program:

To compile the program, follow these steps:
1. Clean Previous Builds:
```bash
make clean
```

2. Build the Program:
```bash
make main
```

#### Usage

Provide usage examples or instructions for running the program, including any necessary commands or arguments.
```bash
./object/main
```
or
```bash
make exec
```

## License

This project is licensed under the OpenSSL License and Apache License 2.0.
Please refer to the LICENSE file for detailed information.

    OpenSSL License: https://www.openssl.org/source/license.html.
    Apache License 2.0: http://www.apache.org/licenses/LICENSE-2.0.

## Acknowledgments

This project uses the OpenSSL library, which is licensed under the OpenSSL License and the Apache License 2.0.