
#include "arduino.h"
#include "Timer.h"

Timer timer;

#define lock1 22
#define lock2 23
#define lock3 24

#define equipmentSensor1 A0
#define equipmentSensor2 A1
#define equipmentSensor3 A2

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
    bool sensor=1;
    timer.start();
    switch (lockernumber)

{
case 1:
    while (sensor>=50||timer.read()<=5000)
    {
        sensor=analogRead(equipmentSensor1);
    }
    break;

case 2:
    while (sensor>=50||timer.read()<=5000)
    {
        sensor=analogRead(equipmentSensor2);
    }
    break;

case 3:
    while (sensor>=50||timer.read()<=5000)
    {
        sensor=analogRead(equipmentSensor3);
    }
    break;
}
timer.stop();
}

void waitReturn(int lockernumber){
    bool sensor=0;
    timer.start();
    switch (lockernumber)
{
case 1:
    while (sensor<=50||timer.read()<=5000)
    {
        sensor=analogRead(equipmentSensor1);
    }
    break;

case 2:
    while (sensor<=50||timer.read()<=5000)
    {
        sensor=analogRead(equipmentSensor1);
    }
    break;

case 3:
    while (sensor<=50||timer.read()<=5000)
    {
        sensor=analogRead(equipmentSensor1);
    }
    break;
}
timer.stop();
}
