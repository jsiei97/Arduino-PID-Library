#include <QtCore>
#include <QtTest>

#include "PID_v1.h"
#include "Arduino.h"

class TestPID : public QObject
{
    Q_OBJECT

    private:
    public:
        bool addToFile(QString logFile, QString data);
        QString formatLog(unsigned long time, double value, double setpoint, double output);
        QString formatName(QString name, int num, double value, double setpoint, double output);

    private slots:
        void test_PID_max_min();
        void test_PID_max_min_data();

        void test_PID_simulator_inc();
        void test_PID_simulator_inc_data();

        void test_PID_simulator_inc_wait();
        void test_PID_simulator_inc_wait_data();
};

QString TestPID::formatLog(unsigned long time, double value, double setpoint, double output)
{
    return QString("%1 ; %2 ; %3 ; %4")
        .arg(time/1000)
        .arg(value,    0, 'f', 2)
        .arg(setpoint, 0, 'f', 2)
        .arg(output,   0, 'f', 2);
}

bool TestPID::addToFile(QString logFile, QString data)
{
    logFile.append(".csv");
    QFile file(logFile);
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out << data << "\n";

    //qDebug() << data;

    file.close();

    return true;
}

QString TestPID::formatName(QString name, int num, double value, double setpoint, double output)
{
    name.append(
            QString("_%1_pid_%2_%3_%4")
        .arg(num)
        .arg(value,    0, 'f', 2)
        .arg(setpoint, 0, 'f', 2)
        .arg(output,   0, 'f', 2)
        );
    return name;
}

extern unsigned long my_local_millis;

void TestPID::test_PID_max_min_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<double>("kp");
    QTest::addColumn<double>("ki");
    QTest::addColumn<double>("kd");

    int testCnt = 1000;
    QString name;
    double p,i,d;

    //name = QString("test_max_min_%1").arg(testCnt++);

    /*
    p=2.0;
    i=0.1;
    d=0.0;
    name = formatName("test_max_min", testCnt++, p,i,d);
    QTest::newRow(name.toAscii()) << name << p << i << d;
    */

    for( p=0.5 ; p<=2 ; p+=0.5 )
    {
        for( i=0.1 ; i<=3 ; i+=0.5 )
        {
            for( d=0 ; d<=0.5 ; d+=0.1 )
            {
                name = formatName("test_max_min", testCnt++, p,i,d);
                QTest::newRow(name.toAscii()) << name << p << i << d;
            }
        }
    }
}

void TestPID::test_PID_max_min()
{
    QFETCH(QString, fileName);
    QFETCH(double, kp);
    QFETCH(double, ki);
    QFETCH(double, kd);

    my_local_millis = 1000;
    QCOMPARE((unsigned long)1000, millis());

    double input = 40;
    double setpoint = input+10;
    double output = 0;
    PID pid(&input, &output, &setpoint, kp, ki, kd, DIRECT);

    double max = 100.0;
    double min = 0.0;
    pid.setOutputLimits(min, max);

    pid.setMode(AUTOMATIC);

    addToFile(fileName, "# NEW SESSION");
    addToFile(fileName, formatLog(my_local_millis, input, setpoint, output));
    //qDebug() << setpoint << input << output;

    int failcnt = 1000;
    do
    {
        pid.compute();
        addToFile(fileName, formatLog(my_local_millis, input, setpoint, output));
        my_local_millis += 1000;
        failcnt--;
    } while(output != max && output != min && failcnt != 0);

    if(failcnt == 0)
    {
        qDebug() << "FAIL:" << __LINE__ << "data:" << my_local_millis << input << setpoint << output;
        qDebug() << "FAIL:" << __LINE__ << "pid :" << kp << ki << kd;
        QFAIL("Failcnt to high");
    }

    setpoint = input-10;

    failcnt = 1000;
    do
    {
        pid.compute();
        addToFile(fileName, formatLog(my_local_millis, input, setpoint, output));
        my_local_millis += 1000;
        failcnt--;
    } while(output != max && output != min && failcnt != 0);

    if(failcnt == 0)
    {
        qDebug() << "FAIL:" << __LINE__ << "data:" << my_local_millis << input << setpoint << output;
        qDebug() << "FAIL:" << __LINE__ << "pid :" << kp << ki << kd;
        QFAIL("Failcnt to high");
    }
}

void TestPID::test_PID_simulator_inc_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<double>("kp");
    QTest::addColumn<double>("ki");
    QTest::addColumn<double>("kd");

    int testCnt = 1000;
    QString name;
    double p,i,d;

    //name = QString("test_max_min_%1").arg(testCnt++);

    /*
    p=0.5;
    i=2.0;
    d=0.0;
    name = formatName("test_simulator_inc", testCnt++, p,i,d);
    QTest::newRow(name.toAscii()) << name << p << i << d;
    */

    for( p=0.5 ; p<=3 ; p+=0.5 )
    {
        for( i=0.1 ; i<=3.0 ; i+=0.5 )
        {
            for( d=0 ; d<=0.5 ; d+=0.1 )
            {
                name = formatName("test_simulator_inc", testCnt++, p,i,d);
                QTest::newRow(name.toAscii()) << name << p << i << d;
            }
        }
    }
}

void TestPID::test_PID_simulator_inc()
{
    QFETCH(QString, fileName);
    QFETCH(double, kp);
    QFETCH(double, ki);
    QFETCH(double, kd);

    my_local_millis = 1000;
    QCOMPARE((unsigned long)1000, millis());

    double input = 40;
    double setpoint = input+10;
    double output = 0;
    PID pid(&input, &output, &setpoint, kp, ki, kd, DIRECT);

    double max = 100.0;
    double min = 0.0;
    pid.setOutputLimits(min, max);

    pid.setMode(AUTOMATIC);

    addToFile(fileName, "# NEW SESSION");
    addToFile(fileName, formatLog(my_local_millis, input, setpoint, output));
    //qDebug() << setpoint << input << output;

    int phase = 0;

    int failcnt = 5000;
    int hitcnt = 0;
    do
    {
        pid.compute();
        addToFile(fileName, formatLog(my_local_millis, input, setpoint, output));

        //Let's simulate that the output affects the value
        if(output>=50.1)
            input += (output-50)/10.0;
        else if(output <= 49.9)
            input -= (50-output)/10.0;

        //but it can't go higher than 80 or lower than 20
        if(input>=80)
            input = 80;
        else if(input <= 20)
            input = 20;

        if(input < setpoint+0.5 && input > setpoint-0.5)
            hitcnt++;
        else
            hitcnt=0;

        if(hitcnt > 50)
        {
            hitcnt = 0;
            switch ( phase )
            {
                case 0 :
                    //let's change the setpoint and check that we
                    //can get a second stable point...
                    setpoint = 40;
                    phase++;
                    break;
                case 1 :
                    //let's disrupt the setpoint
                    setpoint = 45;
                    phase++;
                    break;
                case 2 :
                    //let's disrupt the input
                    input = 35;
                    phase++;
                    break;
                case 3 :
                    //let's disrupt the input
                    input = 55;
                    phase++;
                    break;
                default :
                    phase++;
                    break;
            }
        }

        my_local_millis += 1000;
        failcnt--;

    } while(phase <= 4  && failcnt != 0);

    if(failcnt == 0)
    {
        qDebug() << "FAIL:" << __LINE__ << "data:" << my_local_millis << input << setpoint << output;
        qDebug() << "FAIL:" << __LINE__ << "pid :" << kp << ki << kd;
        QFAIL("Failcnt to high");
    }

    //qDebug() << setpoint << input << output;
}

void TestPID::test_PID_simulator_inc_wait_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<double>("kp");
    QTest::addColumn<double>("ki");
    QTest::addColumn<double>("kd");

    int testCnt = 1000;
    QString name;
    double p,i,d;

    /*
    p=1;
    i=2;
    d=0;
    name = formatName("test_simulator_inc_wait", testCnt++, p,i,d);
    QTest::newRow(name.toAscii()) << name << p << i << d;
    */

    for( p=0.5 ; p<=3 ; p+=0.5 )
    {
        for( i=0.1 ; i<=3 ; i+=0.5 )
        {
            for( d=0 ; d<=0.5 ; d+=0.1 )
            {
                name = formatName("test_simulator_inc", testCnt++, p,i,d);
                QTest::newRow(name.toAscii()) << name << p << i << d;
            }
        }
    }
}

void TestPID::test_PID_simulator_inc_wait()
{
    QFETCH(QString, fileName);
    QFETCH(double, kp);
    QFETCH(double, ki);
    QFETCH(double, kd);

    my_local_millis = 1000;
    QCOMPARE((unsigned long)1000, millis());

    double input = 40;
    double setpoint = 50;
    double output = 0;
    PID pid(&input, &output, &setpoint, kp, ki, kd, DIRECT);

    double max = 100.0;
    double min = 0.0;
    pid.setOutputLimits(min, max);

    pid.setMode(AUTOMATIC);

    addToFile(fileName, "# NEW SESSION");
    addToFile(fileName, formatLog(my_local_millis, input, setpoint, output));
    //qDebug() << setpoint << input << output;

    int phase = 0;

    int failcnt = 5000;
    int hitcnt = 0;
    do
    {
        pid.compute();
        addToFile(fileName, formatLog(my_local_millis, input, setpoint, output));

        //Let's simulate that the output affects the value

        if(output<5)
            input -= 0.1;

        if(output>=5)
            input += output/10.0;

        //but it can't go higher than 80 or lower than 20
        if(input>=80)
            input = 80;
        else if(input <= 20)
            input = 20;

        if(input < setpoint+1.0 && input > setpoint-1.0)
            hitcnt++;
        else
            hitcnt=0;

        if(hitcnt > 50)
        {
            hitcnt = 0;
            switch ( phase )
            {
                case 0 :
                    //let's change the setpoint and check that we
                    //can get a second stable point...
                    setpoint = 40;
                    phase++;
                    break;
                case 1 :
                    //let's disrupt the setpoint
                    setpoint = 45;
                    phase++;
                    break;
                case 2 :
                    //let's disrupt the input
                    input = 35;
                    phase++;
                    break;
                case 3 :
                    //let's disrupt the input
                    input = 55;
                    phase++;
                    break;
                default :
                    phase++;
                    break;
            }
        }

        my_local_millis += 1000;
        failcnt--;

    } while(phase <= 4  && failcnt != 0);

    if(failcnt == 0)
    {
        qDebug() << "FAIL:" << __LINE__ << "data:" << my_local_millis << input << setpoint << output;
        qDebug() << "FAIL:" << __LINE__ << "pid :" << kp << ki << kd;
        QFAIL("Failcnt to high");
    }

    //qDebug() << setpoint << input << output;
}

QTEST_MAIN(TestPID)
#include "TestPID.moc"
