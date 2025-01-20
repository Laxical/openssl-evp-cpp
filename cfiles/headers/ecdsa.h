#ifndef ECDSA_H
#define ECDSA_H

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <openssl/evp.h>
#include <openssl/ec.h>
#include <openssl/err.h>

int signData(const unsigned char* data, int data_len, EVP_PKEY* private_key, unsigned char** sig, unsigned int* sig_len);
int verifySignature(const unsigned char* data, int data_len, EVP_PKEY* public_key, unsigned char* sig, unsigned int sig_len);

#endif