#include "headers/ecdsa.h"

using namespace std;

struct OpenSSLFree {
    void operator()(void* ptr) {
        EVP_MD_CTX_free((EVP_MD_CTX*)ptr);
    }
};

template <typename T> 
using OpenSSLPointer = unique_ptr<T, OpenSSLFree>;

int signData(const unsigned char* data, int data_len, EVP_PKEY* private_key, unsigned char** sig, unsigned int* sig_len) {
    OpenSSLPointer<EVP_MD_CTX> context(EVP_MD_CTX_new());
    EVP_PKEY* evp_key = private_key;

    if (EVP_SignInit(context.get(), EVP_sha256()) != 1) {
        return -1;
    }

    if (EVP_SignUpdate(context.get(), data, data_len) != 1) {
        return -1;
    }

    *sig = (unsigned char *)OPENSSL_malloc(EVP_PKEY_size(evp_key));
    if (EVP_SignFinal(context.get(), *sig, sig_len, evp_key) != 1) {
        ERR_print_errors_fp(stderr);
        return -1;
    }

    return 1;
}

int verifySignature(const unsigned char* data, int data_len, EVP_PKEY* public_key, unsigned char* sig, unsigned int sig_len) {
    OpenSSLPointer<EVP_MD_CTX> context(EVP_MD_CTX_new());
    EVP_PKEY* evp_key = public_key;

    if (EVP_VerifyInit(context.get(), EVP_sha256()) != 1) {
        return -1;
    }

    if (EVP_VerifyUpdate(context.get(), data, data_len) != 1) {
        return -1;
    }

    int result = EVP_VerifyFinal(context.get(), sig, sig_len, evp_key);
    if (result == -1) {
        ERR_print_errors_fp(stderr);
        return -1;
    }

    return result;
}

int digestSignData(const unsigned char* data, int data_len, EVP_PKEY* private_key, unsigned char** sig, size_t* sig_len) {
    OpenSSLPointer<EVP_MD_CTX> context(EVP_MD_CTX_new());
    EVP_PKEY* evp_key = private_key;

    if(EVP_DigestSignInit(context.get(), nullptr, EVP_sha256(), nullptr, evp_key) != 1) {
        return -1;
    }

    if(EVP_DigestSignUpdate(context.get(), data, data_len) != 1) {
        return -1;
    }

    *sig = (unsigned char *)OPENSSL_malloc(EVP_PKEY_size(evp_key));
    if(EVP_DigestSignFinal(context.get(), *sig, sig_len) != 1) {
        return -1;
    }

    return 1;
}

int digestVerifyData(const unsigned char* data, int data_len, EVP_PKEY* public_key, unsigned char* sig, unsigned int sig_len) {
    OpenSSLPointer<EVP_MD_CTX> context(EVP_MD_CTX_new());
    EVP_PKEY* evp_key = public_key;

    if(EVP_DigestVerifyInit(context.get(), nullptr, EVP_sha256(), nullptr, public_key) != 1) {
        return -1;
    }

    if(EVP_DigestVerifyUpdate(context.get(), data, data_len) != 1) {
        return -1;
    }

    int result = EVP_DigestVerifyFinal(context.get(), sig, sig_len);
    if (result == -1) {
        ERR_print_errors_fp(stderr);
        return -1;
    }

    return result;
}