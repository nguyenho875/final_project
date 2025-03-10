//=====[#include guards - begin]===============================================
#ifndef _ELEVATOR_SYSTEM_H_
#define _ELEVATOR_SYSTEM_H_

//=====[#include dependencies]=================================================
#include "arm_book_lib.h"
#include "button.h"
#include "matrix_keypad.h"
#include "display.h"
#include "leds.h"
#include "motor.h"

//=====[Declaration of public global variables]===============================
extern bool passwordEntryEnabled;
extern bool wrongCodeActive;
extern bool correctCodeActive;
extern bool returnToGroundFloor;
extern int targetFloor;

//=====[Declarations (prototypes) of public functions]=========================
void elevatorSystemInit();
void smartElevatorSystemRun();

//=====[#include guards - end]=================================================
#endif // _ELEVATOR_SYSTEM_H_
