#ifndef ECDSAKEYGEN_H
#define ECDSAKEYGEN_H

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <openssl/evp.h>
#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/pem.h>

EVP_PKEY *generateECDSAKey();

#endif