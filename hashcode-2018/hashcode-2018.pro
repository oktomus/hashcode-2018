TEMPLATE = app
TARGET = hashcode-2018

SOURCES += main.cpp

HEADERS += \
    io.h \
    data.h \
    solver.h \
    evaluator.h

QMAKE_CXXFLAGS_RELEASE *= -O2 -std=c+11
