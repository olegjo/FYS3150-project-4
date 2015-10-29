TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
	   ../isingmodel.cpp \
    unittests.cpp

HEADERS += ../isingmodel.h \
    unittests.h


INCLUDEPATH += /usr/local/include
