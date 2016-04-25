QT += core gui widgets network

TARGET = server
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    server.cpp \
    serverwindow.cpp \
    ../common/console.cpp \
    ../common/iconsole.cpp

HEADERS  += mainwindow.h \
    server.h \
    serverwindow.h \
    ../common/console.h \
    ../common/iconsole.h

FORMS += \
    serverwindow.ui
