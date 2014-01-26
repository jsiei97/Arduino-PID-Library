/**
 * @file hw_PID_BigPWM.ino
 * @author Johan Simonsson
 * @brief A basic PID test with a relay controlling output
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
#include "BigPWM.h"
#include "LVTS.h"
#include "PID_v1.h"

LoopTimer loopTimer(1000UL); //1s

int pinRelay = 6;
BigPWM pwm;

LVTS lvts(A0, LVTS_LM35);

double setpoint, input, output;
PID myPID(&input, &output, &setpoint,2,5,1, DIRECT);


void setup()
{
    Serial.begin(9600);

    //INTERNAL: an built-in reference, equal to 1.1 volts on the ATmega168 or ATmega328
    analogReference(INTERNAL); //1.1V

    pinMode(pinRelay, OUTPUT);
    pwm.setWindow(5*1000); //5s
    setpoint = 40;

    myPID.setOutputLimits(0, 100);//0..100%
    myPID.setMode(AUTOMATIC);
}

void loop()
{
    loopTimer.mark(millis());

    if(lvts.getTemperature(&input))
    {
        myPID.compute();

        if(pwm.calc(millis(), (unsigned long)output))
        {
            digitalWrite(pinRelay, LOW);
        }
        else
        {
            digitalWrite(pinRelay, HIGH);
        }

        Serial.print((unsigned int)(millis()/1000));
        Serial.print(" ; ");
        Serial.print(input);
        Serial.print(" ; ");
        Serial.print(setpoint);
        Serial.print(" ; ");
        Serial.print(output);
        Serial.println();
    }
    else
    {
        Serial.println("#Sensor error");
    }
    delay(loopTimer.correctedTime(millis()));
}
