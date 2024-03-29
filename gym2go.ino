#include "src/crypto.h"
#include "src/gym2go_GSM.h"
#include "src/scanner.h"
#include "src/lockerware.h"
//lockernumbers
/*
#define lock1 22
#define lock2 23
#define lock3 24

#define equipmentSensor1 a0
#define equipmentSensor2 a1
#define equipmentSensor3 a2
*/
;
int count = 0;
long GLOBEL_TIME = 0;

long start_time = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);  
  digitalWrite(13, LOW);

  //set all of the lockerpins and 
  setupLockerPins();

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
  // do not delete these code

 // do not delete these code
  start_time = millis()/1000;
  // Serial.print("start: ");
  // Serial.println(start_time);
  String qrString  = get_qr_string();
  //  Serial.print("the qr code is: ");
    // Serial.println(qrString);
  qrString = qrString.substring(0,qrString.indexOf("*"));
  if(qrString.startsWith("G2G")){

    String data[5] = {};
    long current_time = GLOBEL_TIME + start_time;
    if(verify(qrString, data, current_time)){
      //**********************************************************
      //unlock the door
      int locker = data[2].toInt();
      int flag = data[3].toInt();
      unlock(locker);
      if (flag == 0){
        waitTakeout(locker);
      }else{
        waitReturn(locker);
      }
      lock(locker);
      if (flag==1){
        delay(5000);
        checkReturn(locker);
      }
      
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
      publish("history", "{\"requestId\":" + data[1] + ",  \"type\":\"unlock\"}");
      // publish("start", "0");
      // publish("history", "aaa");
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
  // Serial.println("Heartbeat.");

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
