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

    unsigned char* data1 = reinterpret_cast<unsigned char*>(const_cast<char*>(data.c_str()));

    unsigned char *sig1= nullptr;
    unsigned int sig_len1 = 0;

    if(signData(data1, sizeof(data1) - 1, private_key, &sig1, &sig_len1) == -1) {
        cout<<"signData() failed...\n";
        return 1;
    }

    cout<<"Signature1: ";
    printSignature(sig1, sig_len1);
    cout<< endl;

    int result1 = verifySignature(data1, sizeof(data1) - 1, public_key, sig1, sig_len1);
    cout<<"result1: "<<result1<<endl;

    if (result1 == 1) {
        std::cout << "Signature1 is valid." << endl;
    } else {
        std::cout << "Signature1 is invalid." << endl;
    }

    unsigned char *sig2 = nullptr;
    size_t sig_len2 = 0;

    unsigned char* data2 = reinterpret_cast<unsigned char*>(const_cast<char*>(data.c_str()));

    if(digestSignData(data2, sizeof(data2) - 1, private_key, &sig2, &sig_len2) == -1) {
        cout<<"digestSignData() failed...\n";
        return 1;
    }

    cout<<"\nSignature2: ";
    printSignature(sig2, sig_len2);
    cout<< endl;

    int result2 = digestVerifyData(data2, sizeof(data2) - 1, public_key, sig2, sig_len2);
    cout<<"result2: "<<result2<<endl;

    if (result2 == 1) {
        std::cout << "Signature2 is valid." << endl;
    } else {
        std::cout << "Signature2 is invalid." << endl;
    }

    // unsigned char *sig3 = nullptr;
    // unsigned int sig_len3 = 0;

    // unsigned char* data3 = reinterpret_cast<unsigned char*>(const_cast<char*>(data.c_str()));

    // if(signData(data3, sizeof(data3) - 1, private_key, &sig3, &sig_len3) == -1) {
    //     cout<<"signData() failed...\n";
    //     return 1;
    // }

    // cout<<"\nSignature3: ";
    // printSignature(sig3, sig_len3);
    // cout<< endl;

    // int result3 = verifySignature(data3, sizeof(data3) - 1, public_key, sig3, sig_len3);
    // cout<<"result3: "<<result3<<endl;

    // if (result3 == 1) {
    //     std::cout << "Signature3 is valid." << endl;
    // } else {
    //     std::cout << "Signature3 is invalid." << endl;
    // }

    return 0;
}