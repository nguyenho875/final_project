//=====[Libraries]=============================================================

#include "elevator_system.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    elevatorSystemInit();
    while (true) {
        elevatorSystemRun();
    }
}