//=====[#include guards - begin]===============================================
#ifndef _MOTOR_H_
#define _MOTOR_H_

//=====[Declarations (prototypes) of public functions]=========================
void motorControlInit();
void bringToLevel(int level);
void returnToFirstFloor();
int floorLevelRead();

//=====[#include guards - end]=================================================
#endif // _MOTOR_H_
