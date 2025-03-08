//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "leds.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut redLed(D11);
DigitalOut greenLed(D12);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void ledsInit()
{
    redLed = OFF;
    greenLed = OFF;
}

void redLedUpdate( bool state )
{
    redLed = state;
}

void greenLedUpdate( bool state )
{
    greenLed = state;
}

//=====[Implementations of private functions]==================================

