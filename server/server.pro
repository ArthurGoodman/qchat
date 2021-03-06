QT += core gui widgets network

TARGET = server
TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    serverwindow.cpp \
    ../common/console.cpp \
    ../common/iconsole.cpp \
    ../common/utility.cpp

HEADERS  += \
    server.h \
    serverwindow.h \
    ../common/console.h \
    ../common/iconsole.h \
    ../common/utility.h

FORMS += \
    serverwindow.ui
