TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
	../lib.cpp \
	../isingmodel.cpp

HEADERS += ../lib.h \
	   ../isingmodel.h

INCLUDEPATH += /usr/local/include

