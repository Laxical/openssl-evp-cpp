#include <iostream>
#include "headers/sha256.h"
#include "headers/ecdsa.h"
#include "headers/ecdsa_keygen.h"

using namespace std;

void printSignature(unsigned char *sig, unsigned int sig_len) {
    for (unsigned int i = 0; i < sig_len; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)sig[i];
    }
    std::cout << std::dec << std::endl;
}

bool savePrivateKey(EVP_PKEY* key, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        cerr << "Failed to open file for writing: " << filename << endl;
        return false;
    }
    bool success = PEM_write_PrivateKey(file, key, nullptr, nullptr, 0, nullptr, nullptr);
    fclose(file);
    return success;
}

bool savePublicKey(EVP_PKEY* key, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        cerr << "Failed to open file for writing: " << filename << endl;
        return false;
    }
    bool success = PEM_write_PUBKEY(file, key);
    fclose(file);
    return success;
}

EVP_PKEY* loadPrivateKey(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        cerr << "Failed to open file for reading: " << filename << endl;
        return nullptr;
    }
    EVP_PKEY* key = PEM_read_PrivateKey(file, nullptr, nullptr, nullptr);
    fclose(file);
    return key;
}

EVP_PKEY* loadPublicKey(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        cerr << "Failed to open file for reading: " << filename << endl;
        return nullptr;
    }
    EVP_PKEY* key = PEM_read_PUBKEY(file, nullptr, nullptr, nullptr);
    fclose(file);
    return key;
}

int main() {
    // if this is your first time running uncomment below code to generate a ECC private-public key pair.
    // U can comment this after first execution.

    ////////////////////////////////////////////////

    // EVP_PKEY* key = generateECDSAKey();
    // savePrivateKey(key, "private_key.pem");
    // savePublicKey(key, "public_key.pem");

    ////////////////////////////////////////////////

    EVP_PKEY* private_key = loadPrivateKey("private_key.pem");
    EVP_PKEY* public_key = loadPublicKey("public_key.pem");

    string data = "data";
    string hash;

    if(!sha256(data, hash)) {
        printf("sha256 failed...\n");
        return 1;
    }

    cout<<"Hash: " << hash << endl;

    unsigned char* hashed_data = reinterpret_cast<unsigned char*>(const_cast<char*>(hash.c_str()));

    unsigned char *sig = nullptr;
    unsigned int sig_len = 0;

    if(signData(hashed_data, sizeof(hashed_data) - 1, private_key, &sig, &sig_len) == -1) {
        cout<<"signData() failed...\n";
        return 1;
    }

    cout<<"Signature1: ";
    printSignature(sig, sig_len);
    cout<< endl;

    int result = verifySignature(hashed_data, sizeof(hashed_data) - 1, public_key, sig, sig_len);
    cout<<"result1: "<<result<<endl;

    if (result == 1) {
        std::cout << "Signature1 is valid." << endl;
    } else {
        std::cout << "Signature1 is invalid." << endl;
    }

    unsigned char *sig1 = nullptr;
    unsigned int sig_len1 = 0;

    unsigned char* data1 = reinterpret_cast<unsigned char*>(const_cast<char*>(data.c_str()));

    if(signData(data1, sizeof(data1) - 1, private_key, &sig1, &sig_len1) == -1) {
        cout<<"signData() failed...\n";
        return 1;
    }

    cout<<"\nSignature2: ";
    printSignature(sig, sig_len);
    cout<< endl;

    int result1 = verifySignature(data1, sizeof(data1) - 1, public_key, sig1, sig_len1);
    cout<<"result2: "<<result<<endl;

    if (result1 == 1) {
        std::cout << "Signature2 is valid." << endl;
    } else {
        std::cout << "Signature2 is invalid." << endl;
    }

    return 0;
}