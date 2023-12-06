#include "src/crypto.h"
#include "src/gym2go_GSM.h"

void setup() {
  // put your setup code here, to run once:
  gym2go_GSM_setup();
  setPublicKey(subscribePK());
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  // String hex = "b285d3708a706dc5af3a002e6e39d88ad92b9d2cdeb0d386a4a78847b464d1c3";
  // String signature = "eb836c77b68c5d7218f571750533b055ec6843798f61174bb639b654974f9a65a07518816f02be1852ecc3623ccf6c3514d345bb17d21524caf0bbe8204eab08";
  // String message = "123456";
  // setPublicKey(hex);
  // Serial.println("START");
  // bool flag = verify(signature, message);
  // if(flag){
  //   Serial.println("TRUE");
  // }
  gym2go_GSM_in_loop();
}
