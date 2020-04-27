QT -= gui

TEMPLATE = lib
DEFINES += QTHREADING_LIBRARY

CONFIG += c++11

SOURCES += \
    QThreading/qrunnablethread.cpp \

HEADERS += \
    QThreading/qinterruptable.h \
    QThreading/qrunnablethread.h \
    QThreading/qthreadstate.h \
    QThreading/qthreading_global.h
