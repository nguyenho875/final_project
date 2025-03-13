//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"

#include "button.h"
#include "display.h"
#include "leds.h"
#include "motor.h"  
#include "matrix_keypad.h"

//=====[Declaration and initialization of public global variables]=============
bool buttonPressed = false;  
bool returnToGroundFloor = false;
int targetFloor = 1;
bool passwordEntryEnabled = false;

//=====[Implementations of public functions]===================================
void interfaceInit() {
    displayInit();
    buttonInit();
    ledsInit();
    motorInit();
}

void interfaceBeforeKeypadUpdate()
{
    if (buttonRead() && !buttonPressed) {
        if (returnToGroundFloor) {   // check flag
            displayClear();
            displayCharPositionWrite(0, 0);
            displayStringWrite("Returning to 1F");
            motorReturnToFirstFloor();
            returnToGroundFloor = false;  // Reset flag
        } 
        else {
            displayClear();
            displayCharPositionWrite(0, 0);
            displayStringWrite("Welcome!");
            displayCharPositionWrite(0, 1);
            displayStringWrite("Enter password:");
            passwordEntryEnabled = true;
        }
        buttonPressed = true;
    }
    if (!buttonRead()) {
        buttonPressed = false;
    }
}

void interfaceAfterKeypadUpdate() {
    static int accumulatedTimeRedLED = 0;  // Track accumulated time for red LED

    accumulatedTimeRedLED += TIME_INCREMENT_MS;

    if (keypadWrongCodeActiveRead() ) {
        if (accumulatedTimeRedLED >= 200) { 
            accumulatedTimeRedLED = 0;
            redLedWrite(!redLedRead());  // toggle red Led
        }
    } 
    else {
        redLedWrite(false);  // Stop blinking if correct code is entered
    }
     
    if (keypadValidUserRead()) {
        greenLedWrite(true);
        motorBringToLevel(targetFloor);  //  Move elevator immediately after a valid passcode
        keypadCorrectCodeActiveWrite(false);
        returnToGroundFloor = true;  // Set flag to return after next button press
    } 
    else {
        greenLedWrite(false);  
    }
}

bool interfacePasswordEntryEnabledRead()
{
    return passwordEntryEnabled;
}

void interfacePasswordEntryEnabledWrite(state)
{
    passwordEntryEnabled = state;
}

void interfaceTargetFloorWrite(int level) {
    targetFloor = level;
}

