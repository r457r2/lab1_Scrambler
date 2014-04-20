#-------------------------------------------------
#
# Project created by QtCreator 2014-04-09T21:37:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab1_Scrambler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scrambler.cpp

HEADERS  += mainwindow.h \
    scrambler.h

FORMS    += mainwindow.ui

LIBS += $$PWD/libgmp-10.dll \
      $$PWD/libgmpxx-4.dll

#QMAKE_LFLAGS += -lgmp \
#	    -lgmpxx
