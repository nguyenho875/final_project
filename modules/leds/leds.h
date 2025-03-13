//=====[#include guards - begin]===============================================
#ifndef _LEDS_H_
#define _LEDS_H_

//=====[Declarations (prototypes) of public functions]=========================

void ledsInit();   // initialize green and red leds

void redLedWrite(bool state);    // turn on/off red led with parameter
void greenLedWrite(bool state);  // turn on/off green led with parameter

bool redLedRead();     // read state of red led
bool greenLedRead();  // read state of green led

//=====[#include guards - end]=================================================
#endif // _LEDS_H_
