#include "crypto.h"
#include <Ed25519.h>

//bool generate_time;
uint8_t publicKey[32];
//uint8_t message[2];
//size_t len;
//uint8_t signature[64];

void setPublicKey(String hexPublicKey){
  hexCharacterStringToBytes(publicKey, hexPublicKey.c_str());
  // Serial.print("hex public key: ");
  // Serial.println(hexPublicKey);
}

bool verify(String hexSignature, String message){
  // Serial.print("hex signature: ");
  // Serial.println(hexSignature);
  // Serial.print("message: ");
  // Serial.println(message);
  uint8_t signature[64] = {0};
  hexCharacterStringToBytes(signature, hexSignature.c_str());

  byte message_buffer[message.length() + 1];
  message.getBytes(message_buffer, message.length() + 1);
  bool flag = Ed25519::verify	(signature, publicKey,message_buffer,sizeof(message));
  // Serial.print("result: ");
  // Serial.println(flag);
  return flag;
}



void hexCharacterStringToBytes(byte *byteArray, const char *hexString)
{
    bool oddLength = strlen(hexString) & 1;

    byte currentByte = 0;
    byte byteIndex = 0;

    for (byte charIndex = 0; charIndex < strlen(hexString); charIndex++)
    {
        bool oddCharIndex = charIndex & 1;

        if (oddLength)
        {
            // If the length is odd
            if (oddCharIndex)
            {
                // odd characters go in high nibble
                currentByte = nibble(hexString[charIndex]) << 4;
            }
            else
            {
                // Even characters go into low nibble
                currentByte |= nibble(hexString[charIndex]);
                byteArray[byteIndex++] = currentByte;
                currentByte = 0;
            }
        }
        else
        {
            // If the length is even
            if (!oddCharIndex)
            {
                // Odd characters go into the high nibble
                currentByte = nibble(hexString[charIndex]) << 4;
            }
            else
            {
                // Odd characters go into low nibble
                currentByte |= nibble(hexString[charIndex]);
                byteArray[byteIndex++] = currentByte;
                currentByte = 0;
            }
        }
    }
}

byte nibble(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;

    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    return 0; // Not a valid hexadecimal character
}

