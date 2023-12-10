#ifndef CRYPTO_H
#define CRYPTO_H
#include <Arduino.h>
#include "MD5.h"
#include "StringSplitter.h"

void setKey(String pKey);
bool verify(String content, String data[], long current_time);
#endif