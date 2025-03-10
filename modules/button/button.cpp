//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "button.h"
#include "display.h"
#include "elevator_system.h"

//=====[Declaration of private global variables]===============================
DigitalIn elevatorButton(D10, PullDown);
static bool buttonPressed = false;

//=====[Implementations of public functions]===================================

void updateButton()
{
    bool currentState = elevatorButton.read();
    if (currentState && !buttonPressed) {
        if (returnToGroundFloor) {
            displayClear();
            displayCharPositionWrite(0, 0);
            displayStringWrite("Returning to 1F");
            returnToFirstFloor();
            returnToGroundFloor = false;  // ✅ Reset flag
        } else {
            displayClear();
            displayCharPositionWrite(0, 0);
            displayStringWrite("Welcome!");
            displayCharPositionWrite(0, 1);
            displayStringWrite("Enter password:");
            passwordEntryEnabled = true;
        }
        buttonPressed = true;
    }
    if (!currentState) {
        buttonPressed = false;
    }
}
