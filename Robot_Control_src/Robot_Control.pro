#-------------------------------------------------
#
# Project created by QtCreator 2018-11-14T11:15:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Robot_Control
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
    main.cpp \
    view.cpp \
    framegenerator.cpp \
    uart.cpp \
    objectdetector.cpp \
    tristateregulator.cpp

HEADERS += \
    view.h \
    framegenerator.h \
    uart.h \
    objectdetector.h \
    tristateregulator.h

FORMS += \
    view.ui

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/opencv4
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_videoio
LIBS += -lopencv_tracking
LIBS += -lopencv_calib3d
LIBS += -lwiringPi


