CONFIG += qtestlib debug
TEMPLATE = app
TARGET =
DEFINES += private=public

# Test code
DEPENDPATH += .
INCLUDEPATH += .
SOURCES += TestLoopTimer.cpp

# Code to test
DEPENDPATH  += ../../PID/
INCLUDEPATH += ../../PID/
SOURCES += LoopTimer.cpp

