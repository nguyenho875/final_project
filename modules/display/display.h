//=====[#include guards - begin]=============================================
#ifndef _DISPLAY_H_
#define _DISPLAY_H_

//=====[Declarations (prototypes) of public functions]=========================
void displayInit();   // initialize display
void displayClear();  // clear display
void displayStringWrite(const char * str);   // display string parameter

// place cursor at position parameter before writing string
void displayCharPositionWrite(unsigned char charPositionX, unsigned char charPositionY);   

//=====[#include guards - end]=================================================
#endif // _DISPLAY_H_
