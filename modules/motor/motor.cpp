//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "motor.h"


//=====[Declaration of private defines]========================================

//#define MOTOR_UPDATE_TIME 9
#define PWM_PERIOD 0.001

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalIn button(D10);
DigitalOut AIN1(PF_2);
DigitalOut AIN2(PE_3);
PwmOut PWMA(D13); 

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

//=====[Declaration of external public global variables]=======================
int floorLevel = 1;

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void motorControlInit()
{   
    button.mode(PullDown);
    AIN1 = 0;
    AIN2 = 0;
    PWMA.period(PWM_PERIOD);
    PWMA.write(0.0f);
}

void motorControl() 
{
    if (button){
        while (button){}
        checkAndBringDown();
        delay(100);
        uartUsb.write( "Enter floor level: \r\n", 22 );
        char receivedChar = '\0';
        while (!uartUsb.readable()) {}
        uartUsb.read( &receivedChar, 1 );
        
        int level = receivedChar - '0';
        bringToLevel(level);
    }
}

void motorStop() 
{
    PWMA.write(0.0f);
    AIN1 = 0;
    AIN2 = 0;   
}

void motorUp()
{
    PWMA.write(0.3f);
    AIN1 = 0;
    AIN2 = 1;
    delay(1000);
    motorStop();
    floorLevel += 1;
}

void motorDown()
{
    PWMA.write(0.3f);
    AIN1 = 1;
    AIN2 = 0;
    delay(1000);
    motorStop();
    floorLevel -= 1;
}

int floorLevelRead() {
    return floorLevel;
}

void checkAndBringDown() 
{   // check if elevator is on 1st floor and bring down if not
    if (floorLevel == 1) {
        motorStop();
        return;
    }
    while(floorLevel > 1) {
        motorDown();
        delay(300);
    }
    motorStop();
}

void bringToLevel(int level) {
    // bring elevator to parameter level
    while(floorLevel < level) {
        motorUp();
        delay(300);
    }
    motorStop();
}
//=====[Implementations of private functions]==================================
