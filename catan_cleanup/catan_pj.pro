QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET=catan_pj
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += entities/
INCLUDEPATH += enum/
INCLUDEPATH += externvars/
INCLUDEPATH += widgets/


include($$PWD/entities/entities.pri)
include($$PWD/enum/enum.pri)
include($$PWD/externvars/externvars.pri)
include($$PWD/widgets/widgets.pri)


SOURCES += main.cpp \
    mainwindow.cpp


HEADERS += mainwindow.h


FORMS += mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    picture_sources.qrc
