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
    unsigned long targetTime = 1000;
    LoopTimer loopTime(targetTime);

    unsigned long t1 =  0;
    unsigned long t2 = 10;

    loopTime.mark(t1);
    QCOMPARE( loopTime.correctedTime(t2), targetTime-(t2-t1) );

    t1 = t2;
    t2 += 100; //100ms work, ok

    loopTime.mark(t1);
    QCOMPARE( loopTime.correctedTime(t2), targetTime-(t2-t1) );

    t1 = t2;
    t2 += targetTime+100; //100ms work over the limit!

    loopTime.mark(t1);
    QCOMPARE( loopTime.correctedTime(t2), 0UL );

    t1 = t2;
    t2 += targetTime+500; //500ms work over the limit!

    loopTime.mark(t1);
    QCOMPARE( loopTime.correctedTime(t2), 0UL );

    t1 = t2;
    t2 += 200; //200ms work, ok

    loopTime.mark(t1);
    QCOMPARE( loopTime.correctedTime(t2), targetTime-(t2-t1) );

    t1 = t2;
    t2 = 200; //WARNING wrapp

    loopTime.mark(t1);
    QCOMPARE( loopTime.correctedTime(t2), targetTime-(t2) );

    t1 = t2;
    t2 = 100; //WARNING wrapp

    loopTime.mark(t1);
    QCOMPARE( loopTime.correctedTime(t2), targetTime-(t2) );

    t1 = t2;
    t2 += 200; //200ms work, ok

    loopTime.mark(t1);
    QCOMPARE( loopTime.correctedTime(t2), targetTime-(t2-t1) );
}

QTEST_MAIN(TestLoopTimer)
#include "TestLoopTimer.moc"
