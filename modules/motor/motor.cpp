//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "motor.h"

//=====[Declaration of private defines]========================================
#define PWM_PERIOD 0.001

//=====[Declaration and initialization of public global objects]===============
DigitalOut AIN1(PF_2);
DigitalOut AIN2(PE_3);
PwmOut PWMA(D13);

//=====[Declaration and initialization of private global variables]============
static int floorLevel = 1;

//=====[Implementations of public functions]===================================
void motorInit()
{
    AIN1 = 0;
    AIN2 = 0;
    PWMA.period(PWM_PERIOD);
    PWMA.write(0.0f);
}

void motorBringToLevel(int level) 
{  // has blocking code for ease of implementation, ok because nothing else is running when elevator is moving
    while(floorLevel < level) {
        motorUp();
        delay(300);
    }
    motorStop();
}

void motorReturnToFirstFloor()
{   // has blocking code for ease of implementation, ok because nothing else is running when elevator is moving
    while (floorLevel > 1) {
        motorDown();
        delay(300);
    }
    motorStop();
}

//=====[Implementations of private functions]==================================
static void motorStop()
{
    PWMA.write(0.0f);
    AIN1 = 0;
    AIN2 = 0;
}

static void motorUp()
{
    PWMA.write(0.66f);
    AIN1 = 0;
    AIN2 = 1;
    delay(1000);
    motorStop();
    floorLevel += 1;
}

static void motorDown()
{
    PWMA.write(0.22f);
    AIN1 = 1;
    AIN2 = 0;
    delay(1000);
    motorStop();
    floorLevel -= 1;
}