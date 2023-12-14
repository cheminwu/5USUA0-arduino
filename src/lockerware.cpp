
#include "arduino.h"
#include "Timer.h"

Timer timer;
#define lock1 22
#define lock2 23
#define lock3 24

#define equipmentSensor1 30
#define equipmentSensor2 31
#define equipmentSensor3 32
void lock(int lockerNumber){
    Serial.print("locking locker:");
    Serial.println(lockerNumber);
switch (lockerNumber)
{
case 1:
    digitalWrite(22,0);
    break;

case 2:
    digitalWrite(23,0);
    break;

case 3:
    digitalWrite(24,0);
    break;
}

}
void unlock(int lockerNumber){
    Serial.print("unlocking locker:");
    Serial.println(lockerNumber);
switch (lockerNumber)
{
case 1:
    digitalWrite(22,1);
    break;

case 2:
    digitalWrite(23,1);
    break;

case 3:
    digitalWrite(24,1);
    break;
}
}

void waitTakeout(int lockernumber){
    bool sensor=1;
    timer.start();
    switch (lockernumber)

{
case 1:
    while (sensor==1||timer.read()>=10000)
    {
        sensor=digitalRead(30);
    }
    break;

case 2:
    while (sensor==1||timer.read()>=10000)
    {
        sensor=digitalRead(31);
    }
    break;

case 3:
    while (sensor==1||timer.read()>=10000)
    {
        sensor=digitalRead(32);
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
    while (sensor==0||timer.read()>=10000)
    {
        sensor=digitalRead(30);
    }
    break;

case 2:
    while (sensor==0||timer.read()>=10000)
    {
        sensor=digitalRead(31);
    }
    break;

case 3:
    while (sensor==0||timer.read()>=10000)
    {
        sensor=digitalRead(32);
    }
    break;
}
timer.stop();
}
