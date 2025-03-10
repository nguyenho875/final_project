//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "elevator_system.h"

//=====[Declaration of public global variables]================================
bool passwordEntryEnabled = false;
bool wrongCodeActive = false;
bool correctCodeActive = false;
bool returnToGroundFloor = false;
int targetFloor = 1;  // Floor destination

//=====[Implementations of public functions]===================================

void elevatorSystemInit()
{
    displayInit();
    ledsInit();
    motorControlInit();
}

void smartElevatorSystemRun()
{
    updateButton();
    updateKeypad();
    ledsUpdate();

    if (correctCodeActive) {
        bringToLevel(targetFloor);  // ✅ Move elevator immediately after a valid passcode
        correctCodeActive = false;
        returnToGroundFloor = true;  // ✅ Set flag to return after next button press
    }
}
