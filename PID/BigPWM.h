/**
 * @file BigPWM.h
 * @author Johan Simonsson
 * @brief A big window pwm class
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

#ifndef  __BIGPWM_H
#define  __BIGPWM_H


typedef enum
{
    PWM_T0 = 0,
    PWM_T1,
    PWM_MIN,
    PWM_MAX
} PWMStates;



class BigPWM
{
    private:
        PWMStates state;
        unsigned long t0;
        unsigned long t1;
        unsigned long t2;
        unsigned long windowSize;

    public:
        BigPWM();

        void reset();

        bool calc(unsigned long time, unsigned long out);

        void setWindow(unsigned long windowSize);


};

#endif  // __BIGPWM_H
