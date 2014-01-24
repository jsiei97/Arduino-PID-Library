#include "LoopTimer.h"

// Pin 13 has an LED connected on most Arduino boards.
int led = 13;

LoopTimer loopTimer(500UL); //0.5s
bool blink = false;
int err=0;

void setup()
{
    pinMode(led, OUTPUT);
}

void loop()
{
    //Even if there was a lot of "work"
    //we leave this point after Xs since last time we where here,
    //In this case every 0.5s so we should have a steady blink.
    delay(loopTimer.correctedTime(millis()));

    // This should
    if(blink)
    {
        blink = false;
        digitalWrite(led, LOW);
    }
    else
    {
        blink = true;
        digitalWrite(led, HIGH);
    }


    // Add some "work" that takes time
    if(err < 500)
    {
        err+=50;
    }
    else
    {
        err=0;
    }
    delay(err);
}
