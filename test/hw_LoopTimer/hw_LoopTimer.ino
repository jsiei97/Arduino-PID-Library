/**
 * @file hw_LoopTimer.ino
 * @author Johan Simonsson
 * @brief A LoopTimer test
 */

/*
 * Copyright (C) 2014 Johan Simonsson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
