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
        void test_calc02();
};


/**
 * Normal operation test
 */
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
    for(unsigned long i=0; i<15; i++)
    {
        //100%-25%=75% low time
        if(pwm.calc(i, out) != false)
        {
            qDebug() << "Fail at loop:" << i;
            QFAIL("FAIL");
        }
    }
    for(unsigned long i=15; i<20; i++)
    {
        //then go high the rest (25%)
        if(pwm.calc(i, out) != true)
        {
            qDebug() << "Fail at loop:" << i;
            QFAIL("FAIL");
        }
    }
    for(unsigned long i=20; i<35; i++)
    {
        //then go low
        if(pwm.calc(i, out) != false)
        {
            qDebug() << "Fail at loop:" << i;
            QFAIL("FAIL");
        }
    }
    for(unsigned long i=35; i<40; i++)
    {
        //then go high
        if(pwm.calc(i, out) != true)
        {
            qDebug() << "Fail at loop:" << i;
            QFAIL("FAIL");
        }
    }
}


/**
 * Test the millis wrapp problem
 *
 * On the Arduinio the millis will wrapp once every 50 days
 * what shall we do then?
 * Right now there is a controlled reset and we start over, 
 * so there will be a glich when this happens.
 */
void TestBigPWM::test_calc02()
{
    BigPWM pwm;
    pwm.setWindow(20);

    unsigned int out = 50;

    QCOMPARE(pwm.calc(  0, out), false);// T0 - loop1
    QCOMPARE(pwm.calc(  9, out), false);
    QCOMPARE(pwm.calc( 10, out),  true);// T1
    QCOMPARE(pwm.calc( 20, out),  true);// T2
    QCOMPARE(pwm.calc( 20, out), false);// T0 - loop2
    QCOMPARE(pwm.calc( 31, out),  true);// T1
    QCOMPARE(pwm.calc( 35, out),  true);

    QCOMPARE(pwm.t0, 20UL);
    QCOMPARE(pwm.t1, 30UL);
    QCOMPARE(pwm.t2, 40UL);

    //Now what happens if the time wrapps?
    QCOMPARE(pwm.calc( 15, out),  false);

    //The window whould just reset and get the new values.
    //There will be a jump in operation, but just for this window
    QCOMPARE(pwm.t0, 15UL);
    QCOMPARE(pwm.t1, 25UL);
    QCOMPARE(pwm.t2, 35UL);

    //Now what happens if the time wrapps?
    QCOMPARE(pwm.calc( 0, out),  false);
    QCOMPARE(pwm.t0,  0UL);
    QCOMPARE(pwm.t1, 10UL);
    QCOMPARE(pwm.t2, 20UL);
}



QTEST_MAIN(TestBigPWM)
#include "TestBigPWM.moc"
