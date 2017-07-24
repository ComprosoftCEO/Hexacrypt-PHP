#ifndef HEXACRYPT_HEADER
#define HEXACRYPT_HEADER

//Headers to ALWAYS include
#include <phpcpp.h>
#include <iostream>
#include <Datatypes.h>
#include <string>

extern Php::Value Hexacrypt_Encrypt(Php::Parameters &parameters);
extern Php::Value Hexacrypt_Decrypt(Php::Parameters &parameters);

#endif
