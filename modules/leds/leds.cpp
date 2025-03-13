//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"

#include "leds.h"

//=====[Declaration and initialization of public global objects]===============

DigitalOut redLed(D12);
DigitalOut greenLed(D11);

//=====[Implementations of public functions]===================================
void ledsInit() {
    redLed = 0;
    greenLed = 0;
}

void redLedWrite(bool state) {
    redLed  = state;
}

void greenLedWrite(bool state) {
    greenLed  = state;
}

bool redLedRead() {
    return redLed;
}

bool redLedRead() {
    return greenLed;
}


