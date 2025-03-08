//=====[#include guards - begin]===============================================

#ifndef _LEDS_H_
#define _LEDS_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void ledsInit();    // initialize green and red LEDs to off
void redLedUpdate( bool state );  // turn on/off red led with parameter
void greenLedUpdate( bool state ) // turn on/off green led with parameter
 
//=====[#include guards - end]=================================================

#endif // _LEDS_H_