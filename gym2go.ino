#include "src/crypto.h"
#include "src/gym2go_GSM.h"
#include "src/scanner.h"

int count = 0;
long GLOBEL_TIME = 0;

long start_time = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  gym2go_GSM_setup();
  // subscribe key and globel time.
  while(subscribePK() == "" || startTime() == "0"){
    gym2go_GSM_in_loop();
    delay(200);
    continue;
  }
  setKey(subscribePK());
  // set up scanner
  scanner_setup();
  // Serial.println(startTime());
  char *endPtr;
  //globel time set up
  GLOBEL_TIME = strtol(startTime().c_str(), &endPtr, startTime().length());
  Serial.print("system start time: ");
  Serial.print(startTime());
  Serial.println(" seconds since January 1, 1970, 00:00:00 GTM.");
  Serial.println("timer is on.");
  Serial.println("system is ready.");

  system_ready_blink();
}

void loop() {
  start_time = millis()/1000;
  // Serial.print("start: ");
  // Serial.println(start_time);
  String qrString  = get_qr_string();
  qrString = qrString.substring(0,qrString.indexOf("*"));
  if(qrString.startsWith("G2G")){
    // Serial.print("the qr code is: ");
    // Serial.println(qrString);

    String data[5] = {};
    long current_time = GLOBEL_TIME + start_time;
    if(verify(qrString, data, current_time)){
      //**********************************************************
      //unlock the door

      
      //**********************************************************
      Serial.print("request: ");
      Serial.print(data[1]);
      Serial.print(" locker: ");
      Serial.print(data[2]);
      Serial.print(" flag: ");
      Serial.println(data[3]);
      door_unlock_blink();
      Serial.println("unlock the door.");


      //send the log
      publish("history", "{\"requestId\":\"" + data[1] + "\",  \"type\":\"unlock\"}");
    }
  }
  


  // subscribe new key every 60 seconds
  if(count == 60){
    gym2go_GSM_in_loop();
    setKey(subscribePK());
    // Serial.println(subscribePK());
    count = 0;
  }

  
  // put your main code here, to run repeatedly:


  count = count + 1; 
  delay(1000);

}





void system_ready_blink(){
  for(int i = 0;i < 5; i++){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }
}

void door_unlock_blink(){
  for(int i = 0;i < 3; i++){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }
}
