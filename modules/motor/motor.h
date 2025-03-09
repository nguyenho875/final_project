//=====[#include guards - begin]===============================================

#ifndef _MOTOR_H_
#define _MOTOR_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void motorControlInit();
void motorControl(); 
int floorLevelRead();
void checkAndBringDown();
void bringToLevel(int level);

//=====[#include guards - end]=================================================

#endif // _MOTOR_H_
