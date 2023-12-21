#include "scanner.h"
#include <SoftwareSerial.h>


SoftwareSerial SerialScanner(52,53); // RX, TX


void scanner_setup(){
      SerialScanner.begin(9600);
}

String get_qr_string(){
    SerialScanner.begin(9600);
    // Serial.println("into get qr string."); // Print the Byte
    char customBuffer[200];
     int customBufferIndex = 0;
    if (SerialScanner.available()) // Check if there is Incoming Data in the Serial Buffer.
    {
        
        // Serial.println("scanner available."); // Print the Byte
        while (SerialScanner.available()) // Keep reading Byte by Byte from the Buffer till the Buffer is empty
        {
            char incomingChar = SerialScanner.read(); // Read 1 Byte of data and store it in a character variable
            // Serial.print(incomingChar); // Print the Byte
            customBuffer[customBufferIndex] = incomingChar;
            customBufferIndex++;
            // delay(5); // A small delay
            // Serial.print("-"); // Print the Byte
        }
    }else{
        //  Serial.println("scanner not available."); // Print the Byte
    }
    return String(customBuffer);
}