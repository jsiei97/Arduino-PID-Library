/**
 * @file hw_BigPWM.ino
 * @author Johan Simonsson
 * @brief A basic test to show big window PWM
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

#include "BigPWM.h"

// Pin 13 has an LED connected on most Arduino boards.
int led = 13;

BigPWM pwm;

void setup()
{
    pinMode(led, OUTPUT);

    pwm.setWindow(10*1000); //10s
}

void loop()
{
    //LED On for 20% at 10s.
    if(pwm.calc(millis(), 20))
    {
        digitalWrite(led, HIGH);
    }
    else
    {
        digitalWrite(led, LOW);
    }
}
