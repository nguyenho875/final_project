//=====[Libraries]=============================================================

#include "arm_book_lib.h"

#include "elevator_system.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void smartHomeSystemInit()
{
    userInterfaceInit();
    fireAlarmInit();
    pcSerialComInit();
    motorControlInit();
}

void smartHomeSystemUpdate()
{
    userInterfaceUpdate();
    fireAlarmUpdate();    
    pcSerialComUpdate();
    eventLogUpdate();
    motorControlUpdate();
    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
