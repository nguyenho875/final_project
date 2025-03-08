//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "button.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalIn button(D10);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void buttonInit()
{
    button.mode(PullDown);
}

bool buttonStateRead()
{
    return button;
}

//=====[Implementations of private functions]==================================

