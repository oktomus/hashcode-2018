TEMPLATE = app
TARGET = test-round-2018

SOURCES += main.cpp \
    pizza.cpp

INCLUDEPATH += ..
LIBS += -L../core -lcore

HEADERS += \
    pizza.h
