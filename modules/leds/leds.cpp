//=====[Libraries]=============================================================
#include "mbed.h"
#include "leds.h"
#include "elevator_system.h"
#include "motor.h"  // ✅ Include motor to track elevator movement
#include "matrix_keypad.h"

//=====[Declaration of private global objects]=================================

DigitalOut redLED(D12);
DigitalOut greenLED(D11);

//=====[Declaration of private global variables]===============================
static uint32_t lastToggleTime = 0;

//=====[Implementations of public functions]===================================
void ledsInit() {
    redLED = 0;
    greenLED = 0;
    lastToggleTime = Kernel::Clock::now().time_since_epoch().count();
}

void ledsUpdate() {
    uint32_t currentTime = Kernel::Clock::now().time_since_epoch().count();

    // ✅ Blinking red LED when wrong passcode entered
    if (wrongCodeActive) {
        if (currentTime - lastToggleTime >= 200) { // Blinking interval
            lastToggleTime = currentTime;
            redLED = !redLED;
        }
    } else {
        redLED = 0;  // Stop blinking if correct code is entered
    }
}

    // ✅ Green LED lights up when the elevator is moving
 //   if (validUser) {
   //     greenLED = 1;
     //   } else {
       //     greenLED = 0;  // Turn off green LED when stopped at floor 1

