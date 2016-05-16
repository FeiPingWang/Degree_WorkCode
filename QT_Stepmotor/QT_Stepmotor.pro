#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T11:09:15
#
#-------------------------------------------------

QT       += core gui

TARGET = QT_Stepmotor
TEMPLATE = app


SOURCES += main.cpp\
        stepmotor.cpp \
    setcanpar.cpp \
    ThreadRec.cpp \
    debugwindow.cpp \
    setmotorpar.cpp

HEADERS  += stepmotor.h \
    setcanpar.h \
    Headed.h \
    Threadrec.h \
    debugwindow.h \
    setmotorpar.h

FORMS    += stepmotor.ui \
    setcanpar.ui \
    debugwindow.ui \
    setmotorpar.ui

OTHER_FILES += \
    readme.txt
