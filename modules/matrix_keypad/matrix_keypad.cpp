//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "matrix_keypad.h"
#include "display.h"
#include "elevator_system.h"
#include "motor.h"  // ✅ ADDED MOTOR MODULE
#include "string.h"
#include "stdio.h"

//=====[Declaration of private defines]========================================
#define KEYPAD_NUMBER_OF_ROWS 4
#define KEYPAD_NUMBER_OF_COLS 4
#define DEBOUNCE_DELAY 50  // Adjust as needed for stability

//=====[Declaration of private global variables]===============================
static char matrixKeypadIndexToCharArray[] = {
    '1', '2', '3', 'A',
    '4', '5', '6', 'B',
    '7', '8', '9', 'C',
    '*', '0', '#', 'D'
};

// Define row and column pins
DigitalOut keypadRowPins[KEYPAD_NUMBER_OF_ROWS] = {
    DigitalOut(PB_3),
    DigitalOut(PB_5),
    DigitalOut(PC_7),
    DigitalOut(PA_15)
};

DigitalIn keypadColPins[KEYPAD_NUMBER_OF_COLS] = {
    DigitalIn(PB_12, PullUp),
    DigitalIn(PB_13, PullUp),
    DigitalIn(PB_15, PullUp),
    DigitalIn(PC_6, PullUp)
};

//=====[Declaration of global variables]=======================================
static char enteredCode[5] = {0};
static int codeIndex = 0;
static int wrongAttempts = 0;
static char lastKeyPressed = '\0';
bool validUser = false;
//=====[Implementations of public functions]===================================
void updateKeypad() {
    if (!passwordEntryEnabled) {
        return;
    }
    
    char key = matrixKeypadScan();

    if (key != '\0' && key != lastKeyPressed) {  // Avoid repeating same key if held
        lastKeyPressed = key;

        if (key >= '0' && key <= '9') {  // Only process numeric keys
            if (codeIndex < 4) {
                enteredCode[codeIndex++] = key;
                displayClear();
                displayCharPositionWrite(0, 0);
                displayStringWrite("Passcode:");
                displayCharPositionWrite(0, 1);

                // ✅ Display entered passcode
                char passcodeBuffer[5];
                sprintf(passcodeBuffer, "%s", enteredCode);
                displayStringWrite(passcodeBuffer);
            }
            if (codeIndex == 4) {  // ✅ After 4 digits entered, check credentials
                enteredCode[4] = '\0';
                bool validUser = false;
                int userFloor = 1; // Default to first floor

                struct User {
                    const char* name;
                    int floor;
                    const char* code;
                };

                static const User users[] = {
                    {"Kim",   3, "1234"},
                    {"Bob",   2, "5678"},
                    {"Charlie", 3, "9102"},
                    {"Sunny", 3, "9103"},
                    {"James", 2, "1213"}
                };

                #define NUM_USERS (sizeof(users) / sizeof(users[0]))

                for (int i = 0; i < NUM_USERS; i++) {
                    if (strcmp(enteredCode, users[i].code) == 0) {
                        displayClear();
                        displayCharPositionWrite(0, 0);
                        char welcomeMsg[20];
                        sprintf(welcomeMsg, "Welcome %s", users[i].name);
                        displayStringWrite(welcomeMsg);

                        displayCharPositionWrite(0, 1);
                        displayStringWrite("Floor: ");

                        char floorBuffer[5];
                        sprintf(floorBuffer, "%d", users[i].floor);
                        displayStringWrite(floorBuffer);

                        userFloor = users[i].floor;  // Store the user’s floor
                        validUser = true;
                        correctCodeActive = true;
                        wrongCodeActive = false;
                        passwordEntryEnabled = false;
                        break;
                    }
                }

                if (validUser) {
                    bringToLevel(userFloor);  // ✅ Move the motor to the correct floor
                } else {  // If the password is incorrect
                    wrongAttempts++;
                    displayClear();
                    displayCharPositionWrite(0, 0);
                    displayStringWrite("Invalid code!");

                    wrongCodeActive = true;

                    if (wrongAttempts >= 3) {  // ✅ System shutdown after 3 failed attempts
                        displayClear();
                        displayCharPositionWrite(0, 0);
                        displayStringWrite("System shut down");

                        Timer shutdownTimer;
                        shutdownTimer.start();

                        // ✅ 10-second system lockdown
                        while (shutdownTimer.elapsed_time().count() < 10000000) {
                            ThisThread::sleep_for(50ms);
                        }
                        shutdownTimer.stop();

                        wrongAttempts = 0;
                        passwordEntryEnabled = false;
                        wrongCodeActive = false;
                        displayClear();
                    }
                }

                codeIndex = 0;
                memset(enteredCode, 0, sizeof(enteredCode));
            }
        }
    }

    if (key == '\0') {  // ✅ Reset lastKeyPressed when no key is being pressed
        lastKeyPressed = '\0';
    }
}

//=====[Implementations of private functions]==================================
char matrixKeypadScan() {  
    int row, col;

    for (row = 0; row < KEYPAD_NUMBER_OF_ROWS; row++) {
        // Set all rows HIGH first
        for (int i = 0; i < KEYPAD_NUMBER_OF_ROWS; i++) {
            keypadRowPins[i] = 1;
        }

        // Set the current row LOW
        keypadRowPins[row] = 0;
        ThisThread::sleep_for(5ms); // Small delay for stability

        for (col = 0; col < KEYPAD_NUMBER_OF_COLS; col++) {
            if (keypadColPins[col].read() == 0) { // Key is pressed
                ThisThread::sleep_for(DEBOUNCE_DELAY);
                
                // Wait for key release
                while (keypadColPins[col].read() == 0) {
                    ThisThread::sleep_for(5ms);
                }

                return matrixKeypadIndexToCharArray[row * KEYPAD_NUMBER_OF_COLS + col];
            }
        }
    }
    return '\0'; // No key pressed
}
