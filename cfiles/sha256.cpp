#include "headers/sha256.h"

using namespace std;

struct OpenSSLFree {
    void operator()(void* ptr) {
        EVP_MD_CTX_free((EVP_MD_CTX*)ptr);
    }
};

template <typename T> 
using OpenSSLPointer = unique_ptr<T, OpenSSLFree>;

bool sha256(string& unhashed, string& hashed) {
    OpenSSLPointer<EVP_MD_CTX> context(EVP_MD_CTX_new());

    if(context.get() == NULL) {
        return false;
    }

    if(!EVP_DigestInit_ex(context.get(), EVP_sha256(), NULL)) {
        return false;
    }

    if(!EVP_DigestUpdate(context.get(), unhashed.c_str(), unhashed.length())) {
        return false;
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;

    if(!EVP_DigestFinal_ex(context.get(), hash, &lengthOfHash)) {
        return false;
    }

    std::stringstream ss;
    for(unsigned int i = 0; i < lengthOfHash; ++i)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    hashed = ss.str();
    return true;
}