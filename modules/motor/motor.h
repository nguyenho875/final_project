//=====[#include guards - begin]===============================================
#ifndef _MOTOR_H_
#define _MOTOR_H_

//=====[Declarations (prototypes) of public functions]=========================
void motorInit();  // initialize motor
void motorBringToLevel(int level);  // Move the elevator to the specified floor
void motorReturnToFirstFloor();  // bring elevator back to first floor

//=====[#include guards - end]=================================================
#endif // _MOTOR_H_
