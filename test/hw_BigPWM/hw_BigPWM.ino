#include "BigPWM.h"

// Pin 13 has an LED connected on most Arduino boards.
int led = 13;

BigPWM pwm;

void setup() {                
    pinMode(led, OUTPUT);

    pwm.setWindow(10*1000); //10s
}

void loop() {

    //LED On for 20% at 10s.
    if(pwm.calc(millis(), 20))
    {
        digitalWrite(led, LOW);    
    }
    else
    {
        digitalWrite(led, HIGH);
    }
}
