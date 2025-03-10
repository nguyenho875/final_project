//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "motor.h"

//=====[Declaration of private defines]========================================
#define PWM_PERIOD 0.001

//=====[Declaration of private global variables]===============================
DigitalOut AIN1(PF_2);
DigitalOut AIN2(PE_3);
PwmOut PWMA(D13);

static int floorLevel = 1;

//=====[Implementations of public functions]===================================

void motorControlInit()
{
    AIN1 = 0;
    AIN2 = 0;
    PWMA.period(PWM_PERIOD);
    PWMA.write(0.0f);
}

void motorStop()
{
    PWMA.write(0.0f);
    AIN1 = 0;
    AIN2 = 0;
}

void motorUp()
{
    PWMA.write(0.58f);
    AIN1 = 0;
    AIN2 = 1;
    delay(1000);
    motorStop();
    floorLevel += 1;
}

void motorDown()
{
    PWMA.write(0.18f);
    AIN1 = 1;
    AIN2 = 0;
    delay(1000);
    motorStop();
    floorLevel -= 1;
}

int floorLevelRead()
{
    return floorLevel;
}

void bringToLevel(int level)
{
    while (floorLevel < level) {
        motorUp();
        delay(300);
    }
    motorStop();
}

void returnToFirstFloor()
{
    while (floorLevel > 1) {
        motorDown();
        delay(300);
    }
    motorStop();
}
