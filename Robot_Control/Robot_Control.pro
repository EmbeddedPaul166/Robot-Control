#-------------------------------------------------
#
# Project created by QtCreator 2018-11-14T11:15:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Robot_Control
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        view.cpp \
    framegenerator.cpp \
    globals.cpp \
    uart.cpp \
    objectdetector.cpp

HEADERS += \
        view.h \
    framegenerator.h \
    globals.h \
    uart.h \
    objectdetector.h

FORMS += \
        view.ui


INCLUDEPATH += /usr/local/include/opencv4
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_videoio
LIBS += -lopencv_tracking

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


