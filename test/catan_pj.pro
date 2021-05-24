QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET=catan_pj
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    construction_button.cpp \
    main.cpp \
    mainwindow.cpp \
    point.cpp \
    point_disp.cpp \
    terrain.cpp

HEADERS += \
    construction_button.h \
    construction_enum.h \
    externvars.h \
    house_enum.h \
    mainwindow.h \
    player_enum.h \
    player_state_enum.h \
    point.h \
    point_disp.h \
    terrain.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    picture_sources.qrc
