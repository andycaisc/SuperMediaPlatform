#-------------------------------------------------
#
# Project created by QtCreator 2015-05-04T21:24:59
#
#-------------------------------------------------

QT       += core gui widgets multimedia

TARGET = SuperMediaProducerTester
TEMPLATE = app

INCLUDEPATH += "../include"
LIBS += -L../../lib -lSuperMediaProducerd -lavcodec -lavutil -lavformat -lavdevice -lswscale


SOURCES += main.cpp\
        MediaTestPlayer.cpp \
    VideoWidgetSurface.cpp \
    YUV420PVideoBuffer.cpp \
    VideoWidget.cpp \
    VideoDataSource.cpp \
    RGB24VideoBuffer.cpp

HEADERS  += MediaTestPlayer.h \
    VideoWidgetSurface.h \
    YUV420PVideoBuffer.h \
    VideoWidget.h \
    VideoDataSource.h \
    RGB24VideoBuffer.h
