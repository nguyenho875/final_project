//=====[#include guards - begin]===============================================

#ifndef _MATRIX_KEYPAD_H_
#define _MATRIX_KEYPAD_H_

//=====[Declarations (prototypes) of public functions]=========================

void keypadUpdate();  
// called after elvator button is pressed and elevator box is down on floor 1, or after system shutdown.
// performs everything related to the matrix keypad, or basically 
    // the whole authentication functionality of the system.
// track key entered through keypad, display on lcd, and verify if code entered is correct
// if code is correct, display user's name and floor level. 
    // also assign the variable target floor with the according floor number to next move elevator
// if code is incorrect, keep checking until correct, or until 3 tries are attempted, after which 
// is system shutdown and reset


// functions called by user interface to either write or read states of checking variables
void keypadCorrectCodeActiveWrite(state); 
bool keypadWrongCodeActiveRead();
bool keypadValidUserRead();

//=====[#include guards - end]=================================================
#endif // _MATRIX_KEYPAD_H_
