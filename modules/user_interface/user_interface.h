//=====[#include guards - begin]===============================================
#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

//=====[Declarations (prototypes) of public functions]=========================
void interfaceInit();  // initalize all system components except for matrix keypad

void interfaceBeforeKeypadUpdate();  
// perform system functionality before keypad is required
// check when elevator button is pressed to bring down elevator or allow user to enter code
// display welcome message when button is pressed to use elevator

void interfaceAfterKeypadUpdate();
// perform system functionality after code is entered through keypad and checked for verification
// flash red led if code is incorrect. turn on green led is code is correct, while the elevator is moving
// also bring elevator to the correct floor level

// functions called by matrix keypad to either read or write checking variables
bool interfacePasswordEntryEnabledRead();
void interfacePasswordEntryEnabledWrite(state);

// called by matrix keypad to assign correct floor level to variable target floor to know where to go
void interfaceTargetFloorWrite(int level);

//=====[#include guards - end]=================================================
#endif // _USER_INTERFACE_H_
