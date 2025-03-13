//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "stdio.h"   // c library for more operational functions
#include "string.h"  // c library for more string functions

#include "matrix_keypad.h"
#include "display.h"
#include "user_interface.h"

//=====[Declaration of private defines]========================================
#define KEYPAD_NUMBER_OF_ROWS 4
#define KEYPAD_NUMBER_OF_COLS 4
#define DEBOUNCE_KEY_TIME_MS   40

//=====[Declaration and initialization of public global objects]===============
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

//=====[Declaration and initialization of public global variables]=============
char enteredCode[5] = {0};
int codeIndex = 0;
int wrongAttempts = 0;
char lastKeyPressed = '\0';

bool correctCodeActive = false;
bool wrongCodeActive = false;
bool validUser = false;

//=====[Declaration of private global variables]===============================
static char matrixKeypadIndexToCharArray[] = {
    '1', '2', '3', 'A',
    '4', '5', '6', 'B',
    '7', '8', '9', 'C',
    '*', '0', '#', 'D'
};

//=====[Declarations (prototypes) of private functions]========================
static char matrixKeypadScan(); 

//=====[Implementations of public functions]===================================
void keypadUpdate() {
    if (!interfacePasswordEntryEnabledRead()) {
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

                // Display entered passcode
                char passcodeBuffer[5];
                sprintf(passcodeBuffer, "%s", enteredCode);
                displayStringWrite(passcodeBuffer);
            }
            if (codeIndex == 4) {  //  After 4 digits entered, check credentials
                enteredCode[4] = '\0';
                validUser = false;

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

                        validUser = true;
                        interfaceTargetFloorWrite(users[i].floor);
                        correctCodeActive = true;
                        wrongCodeActive = false;
                        interfacePasswordEntryEnabledWrite(false);
                        break;
                    }
                }
            } 
            else {  // If the password is incorrect
                wrongAttempts++;
                displayClear();
                displayCharPositionWrite(0, 0);
                displayStringWrite("Invalid code!");

                wrongCodeActive = true;

                if (wrongAttempts >= 3) {  // System shutdown after 3 failed attempts
                    displayClear();
                    displayCharPositionWrite(0, 0);
                    displayStringWrite("System shut down");

                    delay(10000); // 10 seconds system shutdown

                    wrongAttempts = 0;
                    interfacePasswordEntryEnabledWrite(false);
                    wrongCodeActive = false;
                    displayClear();
                }
            }
            codeIndex = 0;
            memset(enteredCode, 0, sizeof(enteredCode));
        }
    }

    if (key == '\0') {  // Reset lastKeyPressed when no key is being pressed
        lastKeyPressed = '\0';
    }
}

void keypadCorrectCodeActiveWrite(state)
{
    correctCodeActive = state;
}

bool keypadWrongCodeActiveRead() {
    return wrongCodeActive;
}

bool keypadValidUserRead() {
    return validUser;
}

//=====[Implementations of private functions]==================================
static char matrixKeypadScan() {  
    int row, col;

    for (row = 0; row < KEYPAD_NUMBER_OF_ROWS; row++) {
        // Set all rows HIGH first
        for (int i = 0; i < KEYPAD_NUMBER_OF_ROWS; i++) {
            keypadRowPins[i] = 1;
        }
        // Set the current row LOW
        keypadRowPins[row] = 0;

        for (col = 0; col < KEYPAD_NUMBER_OF_COLS; col++) {
            if (keypadColPins[col].read() == 0) { // Key is pressed
                ThisThread::sleep_for(DEBOUNCE_KEY_TIME_MS);
                
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
