#include "LoopTimer.h"

// Pin 13 has an LED connected on most Arduino boards.
int led = 13;

unsigned long diff = 0;
unsigned long timeNew = 0;
unsigned long timeOld = 0;
#define SLEEP_TIME 1000UL

LoopTimer loopTimer(SLEEP_TIME);
bool blink = false;
int err=0;

void setup()
{
    Serial.begin(9600);    
    pinMode(led, OUTPUT);
}

void loop()
{
    loopTimer.mark(millis());

    timeNew = millis();
    diff = timeNew-timeOld;
    timeOld = timeNew;

    Serial.print("Time: ");
    Serial.print(diff);
    Serial.print(" - ");
    Serial.println(timeNew);

    if( diff < (SLEEP_TIME)-5 || diff > (SLEEP_TIME)+5)
    {
        Serial.print("Err : ");
        Serial.println(diff);
    }

    // Blink at a steady rate
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

    delay(loopTimer.correctedTime(millis()));
}
