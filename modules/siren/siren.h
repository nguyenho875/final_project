//=====[#include guards - begin]===============================================

#ifndef _SIREN_H_
#define _SIREN_H_

typedef enum {
    RGB_LED_RED,
    RGB_LED_GREEN,
    RGB_LED_BLUE,
} lightSystem_t;

//=====[Declarations (prototypes) of public functions]=========================

void sirenInit();
bool sirenStateRead();
void sirenStateWrite( bool state );
void sirenUpdate( int strobeTime );

void brightControlInit();
void setDutyCycle( lightSystem_t light, float dutyCycle );


//---Lights

void lightSystemInit();
void lightSystemUpdate();
void lightLevelControlInit();
void lightLevelControlUpdate();
float lightLevelControlRead();

//=====[#include guards - end]=================================================

#endif // _SIREN_H_
