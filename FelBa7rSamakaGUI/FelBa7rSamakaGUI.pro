#-------------------------------------------------
#
# Project created by QtCreator 2013-06-16T19:35:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        m.cpp \
    SharkRLE.cpp \
    Shark.cpp \
    RunLengthEncoding.cpp \
    Ocean.cpp \
    FishRLE.cpp \
    Fish.cpp \
    EmptyRLE.cpp \
    Empty.cpp \
    DoubleLinkedListNode.cpp \
    DoubleLinkedList.cpp \
    CreatureRLE.cpp \
    Creature.cpp \
    mainwindow.cpp \
    inputs.cpp \
    buttons.cpp \
    buttonnumber.cpp \
    oceanview.cpp \
    RLENode.cpp \
    RLELinkedListStack.cpp \
    OceanNode.cpp \
    LinkedListStack.cpp \
    stack.cpp \
    rleshow.cpp \
    minimaxshow.cpp \
    help.cpp

HEADERS  += m.h \
    SharkRLE.h \
    Shark.h \
    RunLengthEncoding.h \
    Ocean.h \
    FishRLE.h \
    Fish.h \
    EmptyRLE.h \
    Empty.h \
    DoubleLinkedListNode.h \
    DoubleLinkedList.h \
    CreatureRLE.h \
    Creature.h \
    mainwindow.h \
    inputs.h \
    buttons.h \
    buttonnumber.h \
    oceanview.h \
    RLENode.h \
    RLELinkedListStack.h \
    OceanNode.h \
    LinkedListStack.h \
    stack.h \
    rleshow.h \
    minimaxshow.h \
    help.h

FORMS    += m.ui \
    mainwindow.ui \
    inputs.ui \
    stack.ui \
    help.ui

RESOURCES += \
    resources.qrc
