QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../HttpClient/client.cpp \
    graphavion.cpp \
    macket.cpp \
    code128.cpp \
    code128item.cpp \
    main.cpp \
    mainwindow.cpp \
    ticket.cpp

HEADERS += \
    ../HttpClient/client.h \
    graphavion.h \
    macket.h \
    mainwindow.h \
    code128.h \
    code128item.h \
    ticket.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../tickets/ticket-twnb.png
