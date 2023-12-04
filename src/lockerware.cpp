#include "arduino.h"
#include "timer.h"

bool dayPassed(){ //start timer in setup code plz
    long millisInDay=86400000;
    long timePassed=Timer.read();
    if (timepassed<millisInDay){
        return 0;
    }
    else if(timepassed>=millisInDay){
        timer.stop();
        timer.start();
        return 1;
    }
}


void lock(int lockerNumber){
switch (lockerNumber);
{
case 1:
    digitalWrite(lock1,0);
    break;

case 2:
    digitalWrite(lock2,0);
    break;

case 3:
    digitalWrite(lock3,0);
    break;
}

}
void unlock(int lockerNumber){
switch (lockerNumber);
{
case 1:
    digitalWrite(lock1,1);
    break;

case 2:
    digitalWrite(lock2,1);
    break;

case 3:
    digitalWrite(lock3,1);
    break;
}
}

void waitTakeout(int lockernumber){
    bool sensor=1;
    switch (lockerNumber);
{
case 1:
    while (sensor==1)
    {
        sensor=digitalRead(equipmentSensor1);
    }
    break;

case 2:
    while (sensor==1)
    {
        sensor=digitalRead(equipmentSensor2);
    }
    break;

case 3:
    while (sensor==1)
    {
        sensor=digitalRead(equipmentSensor3);
    }
    break;
}
}

void waitReturn(int lockernumber){
    bool sensor=0;
    switch (lockerNumber);
{
case 1:
    while (sensor==0)
    {
        sensor=digitalRead(equipmentSensor1);
    }
    break;

case 2:
    while (sensor==0)
    {
        sensor=digitalRead(equipmentSensor2);
    }
    break;

case 3:
    while (sensor==0)
    {
        sensor=digitalRead(equipmentSensor3);
    }
    break;
}
}
