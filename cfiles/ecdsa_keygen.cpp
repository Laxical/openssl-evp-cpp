#include "headers/ecdsa_keygen.h"

using namespace std;

EVP_PKEY* generateECDSAKey() {
    EVP_PKEY* pkey = nullptr;

    pkey = EVP_EC_gen("secp256k1");
    if (pkey == nullptr) {
        abort();
    }

    return pkey;
}