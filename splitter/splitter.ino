/**
 * @file splitter.ino
 * @author Johan Simonsson
 * @brief A 0-10V splitter
 *
 * This code will read a 0-10V input signal and
 * split it in seq onto the outputs.
 *
 * Input Out1 Out2
 * ----- ---- ----
 *    0%   0%   0%
 *   25%  50%   0%
 *   50% 100%   0%
 *   75% 100%  50%
 *  100% 100% 100%
 */

/*
 * Copyright (C) 2015 Johan Simonsson
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

//#define DEBUG

const int ledPin = 9;     // the number of the LED pin
int ledState = LOW;       // ledState used to set the LED
long previousMillis = 0;  // will store last time LED was updated
long interval = 1000;     // interval at which to blink (milliseconds)

int out1 = 5;
int out2 = 6;
int analogPin = A0;
int val = 0;

void setup()
{
#ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Begin");
#endif

    pinMode(out1, OUTPUT);
    pinMode(out2, OUTPUT);

    pinMode(ledPin, OUTPUT);

    analogReference(DEFAULT); //5V ref
}

void loop()
{
    //Split input onto outputs

    // analogRead values go from 0 to 1023 (0..0x3FF)
    // analogWrite values from 0 to 255    (0..0x0FF)
    val = analogRead(analogPin);
#ifdef DEBUG
    Serial.print("Read: ");
    Serial.println(val);
#endif

    //Now 0..0x1FF)
    val = val/2;

    //High or low?
    if(val < 0x100)
    {
        analogWrite(out1, (val & 0xFF));
        analogWrite(out2, 0);
#ifdef DEBUG
        Serial.print("Low : ");
        Serial.println((val & 0xFF));
#endif
    }
    else
    {
        analogWrite(out1, 0xFF);
        analogWrite(out2, (val & 0xFF));
#ifdef DEBUG
        Serial.print("High: ");
        Serial.println((val & 0xFF));
#endif
    }

    //Blink onboard LED so we know it is alive...
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval)
    {
        previousMillis = currentMillis;

        if (ledState == LOW)
        {
            ledState = HIGH;
        }
        else
        {
            ledState = LOW;
        }

        digitalWrite(ledPin, ledState);
    }
#ifdef DEBUG
    delay(500);
#endif
}
