#include "src/crypto.h"


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  int result = addTwoInts(4,3);
  Serial.println(result);

}

void loop() {
  // put your main code here, to run repeatedly:

}
