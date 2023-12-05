#ifndef CRYPTO_H
#define CRYPTO_H
#include <Arduino.h>

void setPublicKey(String hexPublicKey);
bool verify(String hexSignature, String message);
void hexCharacterStringToBytes(byte *byteArray, const char *hexString);
byte nibble(char c);
#endif