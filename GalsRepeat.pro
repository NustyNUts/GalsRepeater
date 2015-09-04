#-------------------------------------------------
#
# Project created by QtCreator 2015-08-20T10:11:23
#
#-------------------------------------------------

QT       += core gui network positioning

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GalsRepeat
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp \
    client.cpp \
    logic.cpp \
    ship.cpp \
    griditem.cpp \
    shipitem.cpp \
    gals.cpp \
    galsitem.cpp \
    shiptail.cpp

HEADERS  += widget.h \
    client.h \
    logic.h \
    ship.h \
    griditem.h \
    shipitem.h \
    gals.h \
    galsitem.h \
    shiptail.h

FORMS    += widget.ui
