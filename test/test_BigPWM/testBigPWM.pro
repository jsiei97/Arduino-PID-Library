CONFIG += qtestlib debug
TEMPLATE = app
TARGET =
DEFINES += private=public

# Test code
DEPENDPATH += .
INCLUDEPATH += .
SOURCES += TestBigPWM.cpp

# Code to test
DEPENDPATH  += ../../PID/
INCLUDEPATH += ../../PID/
SOURCES += BigPWM.cpp

