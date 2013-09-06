/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include "PID_v1.h"

//Define Variables we'll be connecting to
double setpoint, input, output;

//Specify the links and initial tuning parameters
PID myPID(&input, &output, &setpoint, 2, 5, 1, DIRECT);

void setup()
{
    //initialize the variables we're linked to
    input = analogRead(0);
    setpoint = 100;

    //turn the PID on
    myPID.setMode(AUTOMATIC);
}

void loop()
{
    input = analogRead(0);
    myPID.compute();
    analogWrite(3,output);
}
