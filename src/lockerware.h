#ifndef lockerware
#define lockerware

/*checks if a day has passed
    start a timer in setup code or this will not work
    put Timer timer above the setup code and start it
    inside the setup code with timer.start*/
bool dayPassed();

/*locks lockernumber
    when defining which pins will go to the locks
    please use lockn=pin, with n being the lockernumber*/
void lock(int lockernumber);

//unlocks lockernumber, uses same lockn=pin as above
void unlock(int lockernumber);

/*checks if equipment has been taken out of lockernumber
    When defining sensors, use equipmentSensorn=pin
    with n being the lockernumber*/
void waitTakeout(int lockernumber);

/*checks if equipment has been returned
    uses same equipmentSensorn=pin as above*/
void waitReturn(int lockernumber);


#endif
