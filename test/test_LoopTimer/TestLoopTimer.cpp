/**
 * @file TestLoopTimer.cpp
 * @author Johan Simonsson
 * @brief Test for LoopTimer
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

#include "LoopTimer.h"

class TestLoopTimer : public QObject
{
    Q_OBJECT

    private:
    public:

    private slots:
        void test_correctedTime();
};


void TestLoopTimer::test_correctedTime()
{
    LoopTimer loopTime(1000);


    unsigned long t1 = 0;
    QCOMPARE( loopTime.correctedTime(t1), 1000UL);

    // 1000 - 500 = 500
    t1+=500;
    QCOMPARE( loopTime.correctedTime(t1),  500UL);

    t1+=500;
    QCOMPARE( loopTime.correctedTime(t1),  500UL);

    // 1000 - 700 = 300
    t1+=700;
    QCOMPARE( loopTime.correctedTime(t1),  300UL);

    // More than sleep time target, aka just go again!
    t1+=1100;
    QCOMPARE( loopTime.correctedTime(t1),    0UL);

    t1+=100;
    QCOMPARE( loopTime.correctedTime(t1),  900UL);

    // Test overflow and new time at 200!
    // We ignore that part up to the overflow,
    // but remove the part after overflow.
    // (maybe care later...)
    // 1000 - 200 = 800
    t1 =200;
    QCOMPARE( loopTime.correctedTime(t1),  800UL);

    // But if we start at 0,
    // 1000 - 0 = 1000
    t1 =0;
    QCOMPARE( loopTime.correctedTime(t1),  1000UL);

    // More than sleep time target, aka just go again!
    t1+=1100;
    QCOMPARE( loopTime.correctedTime(t1),    0UL);

    // 1000 - 700 = 300
    t1+=700;
    QCOMPARE( loopTime.correctedTime(t1),  300UL);
}





QTEST_MAIN(TestLoopTimer)
#include "TestLoopTimer.moc"
