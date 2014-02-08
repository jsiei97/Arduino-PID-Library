CONFIG += qtestlib debug
QT     -= gui
TEMPLATE = app
TARGET =
DEFINES += private=public
DEFINES += ARDUINO=101

# Test code
DEPENDPATH += .
INCLUDEPATH += .
SOURCES += TestPID.cpp

# Code to test
DEPENDPATH  += ../../PID/
INCLUDEPATH += ../../PID/
SOURCES += PID_v1.cpp Arduino.c

