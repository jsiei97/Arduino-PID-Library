/**
 * @file Arduino.c
 * @author Johan Simonsson
 * @brief Stub the hw dependent code on the Arduino
 */
#include "Arduino.h"

unsigned long my_local_millis = 0;
unsigned long millis(void)
{
    return my_local_millis;
}
