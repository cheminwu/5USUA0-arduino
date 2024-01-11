
#include "arduino.h"
#include "Timer.h"

Timer timer;

#define lock1 22
#define lock2 23
#define lock3 24

#define equipmentSensor1 'a0'
#define equipmentSensor2 'a1'
#define equipmentSensor3 'a2'

#define hall1 30
#define hall2 31
#define hall3 32

void setupLockerPins(){
    pinMode(lock1, OUTPUT);
    digitalWrite(lock1,LOW);
    pinMode(lock2, OUTPUT);
    digitalWrite(lock2,LOW);
    pinMode(lock3, OUTPUT);
    digitalWrite(lock3,LOW);
    pinMode(equipmentSensor1, INPUT);
    pinMode(equipmentSensor2, INPUT);    
    pinMode(equipmentSensor3, INPUT);
}


void lock(int lockerNumber){
    Serial.print("locking locker:");
    Serial.println(lockerNumber);
switch (lockerNumber)
{
case 1:
    digitalWrite(lock1,LOW);
    break;

case 2:
    digitalWrite(lock2,LOW);
    break;

case 3:
    digitalWrite(lock3,LOW);
    break;
}

}
void unlock(int lockerNumber){
    Serial.print("unlocking locker:");
    Serial.println(lockerNumber);
switch (lockerNumber)
{
case 1:
    digitalWrite(lock1,HIGH);
    break;

case 2:
    digitalWrite(lock2,HIGH);
    break;

case 3:
    digitalWrite(lock3,HIGH);
    break;
}
}

void waitTakeout(int lockernumber){
    int sensor=100;
    timer.start();
    switch (lockernumber)

{
case 1:
    while (sensor>=50&&timer.read()<=5000)
    {
        sensor=analogRead(equipmentSensor1);
        Serial.print("sensorvalue: ");
        Serial.println(sensor);
    }
    break;

case 2:
    while (sensor>=50&&timer.read()<=5000)
    {
        sensor=analogRead(equipmentSensor2);
        Serial.print("sensorvalue: ");
        Serial.println(sensor);
    }
    break;

case 3:
    while (sensor>=50&&timer.read()<=5000)
    {
        sensor=analogRead(equipmentSensor3);
        Serial.print("sensorvalue: ");
        Serial.println(sensor);
    }
    break;
}
timer.stop();
}

void waitReturn(int lockernumber){
    int sensor=0;
    timer.start();
    switch (lockernumber)
{
case 1:
    while (sensor<=50&&timer.read()<=5000)
    {
        sensor=analogRead(equipmentSensor1);
        Serial.print("sensorvalue: ");
        Serial.println(sensor);
    }
    break;

case 2:
    while (sensor<=50&&timer.read()<=5000)
    {
        sensor=analogRead(equipmentSensor1);
        Serial.print("sensorvalue: ");
        Serial.println(sensor);
    }
    break;

case 3:
    while (sensor<=50&&timer.read()<=5000)
    {
        sensor=analogRead(equipmentSensor1);
        Serial.print("sensorvalue: ");
        Serial.println(sensor);
    }
    break;
}
timer.stop();
}

void checkReturn(int lockernumber){
    int weightCheck=0;
    bool doorlock=0;
    switch(lockernumber){
        case 1:
        weightCheck = analogRead(equipmentSensor1);
        doorlock= digitalRead(hall1);
        break;
        case 2:
        weightCheck = analogRead(equipmentSensor2);
        doorlock= digitalRead(hall2);
        break;
        case 3:
        weightCheck = analogRead(equipmentSensor3);
        doorlock= digitalRead(hall3);
        break;
    }
    /*this might need to move into the switch statement because of the difference
    in sensitivity of the sensors*/ 
    if(weightCheck>=150 && doorlock==1)
    {
        //object succesfully returned,send return succesful
        Serial.print("item in locker" );
        Serial.print(lockernumber);
        Serial.println(" has been returned succesfully");

    }
    else
    {
        //object missing or door not closed, send return unsuccesful
        Serial.print("item in locker" );
        Serial.print(lockernumber);
        Serial.println(" has not been returned, initiate doxxing protocol");
    }
}
