#ifndef SHA256_H
#define SHA256_H

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <openssl/evp.h>

bool sha256(std::string& unhashed, std::string& hashed);

#endif