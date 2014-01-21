/**
 * @file TestBigPWM.cpp
 * @author Johan Simonsson
 * @brief Test for BigPWM
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

#include <QtCore>
#include <QtTest>
#include <QDebug>

#include "BigPWM.h"

class TestBigPWM : public QObject
{
    Q_OBJECT

    private:
    public:

    private slots:
        void test_calc01();
};



void TestBigPWM::test_calc01()
{
    BigPWM pwm;

    pwm.setWindow(20);

    //Test 100% PWM
    unsigned int out = 100;
    for(unsigned long i=0; i<44; i++)
    {
        //It should always return true if out is 100%
        if(pwm.calc(i, out) != true)
        {
            qDebug() << "Fail at loop:" << i;
            QFAIL("FAIL");
        }
    }

    //Test 0% PWM
    pwm.reset();
    out = 0;
    for(unsigned long i=0; i<44; i++)
    {
        //It should always return false if out is 0%
        if(pwm.calc(i, out) != false)
        {
            qDebug() << "Fail at loop:" << i;
            QFAIL("FAIL");
        }
    }

    //Test 50% PWM
    pwm.reset();
    out = 50;
    for(unsigned long i=0; i<10; i++)
    {
        //50% start low
        if(pwm.calc(i, out) != false)
        {
            qDebug() << "Fail at loop:" << i;
            QFAIL("FAIL");
        }
    }
    for(unsigned long i=10; i<20; i++)
    {
        //50% then go high
        if(pwm.calc(i, out) != true)
        {
            qDebug() << "Fail at loop:" << i;
            QFAIL("FAIL");
        }
    }
    for(unsigned long i=20; i<30; i++)
    {
        //50% then go low
        if(pwm.calc(i, out) != false)
        {
            qDebug() << "Fail at loop:" << i;
            QFAIL("FAIL");
        }
    }
    for(unsigned long i=30; i<40; i++)
    {
        //50% then go high
        if(pwm.calc(i, out) != true)
        {
            qDebug() << "Fail at loop:" << i;
            QFAIL("FAIL");
        }
    }



    //Test 25% PWM
    pwm.reset();
    out = 25;
    for(unsigned long i=0; i<5; i++)
    {
        //25% start low
        if(pwm.calc(i, out) != false)
        {
            qDebug() << "Fail at loop:" << i;
            QFAIL("FAIL");
        }
    }
    for(unsigned long i=5; i<20; i++)
    {
        //then go high
        if(pwm.calc(i, out) != true)
        {
            qDebug() << "Fail at loop:" << i;
            QFAIL("FAIL");
        }
    }
    for(unsigned long i=20; i<25; i++)
    {
        //then go low
        if(pwm.calc(i, out) != false)
        {
            qDebug() << "Fail at loop:" << i;
            QFAIL("FAIL");
        }
    }
    for(unsigned long i=25; i<40; i++)
    {
        //then go high
        if(pwm.calc(i, out) != true)
        {
            qDebug() << "Fail at loop:" << i;
            QFAIL("FAIL");
        }
    }



}


QTEST_MAIN(TestBigPWM)
#include "TestBigPWM.moc"
