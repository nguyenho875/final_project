//=====[#include guards - begin]=============================================
#ifndef _DISPLAY_H_
#define _DISPLAY_H_

//=====[Declarations (prototypes) of public functions]=========================
void displayInit();
void displayClear();
void displayStringWrite(const char * str);
void displayCharPositionWrite(unsigned char charPositionX, unsigned char charPositionY);

//=====[#include guards - end]=================================================
#endif // _DISPLAY_H_
