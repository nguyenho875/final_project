//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"

#include "elevator_system.h"
#include "user_interface.h"
#include "matrix_keypad.h"

//=====[Implementations of public functions]===================================

void elevatorSystemInit()
{
    interfaceInit();
    // no initilization for matrix keypad
}

void elevatorSystemRun()
{
    interfaceBeforeKeypadUpdate();
    keypadUpdate();
    interfaceAfterKeypadUpdate();
    delay(SYSTEM_TIME_INCREMENT_MS);
}

