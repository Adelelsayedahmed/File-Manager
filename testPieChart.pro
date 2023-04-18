QT       += core gui
QT       += charts
QT       += widgets
LIBS += -lboost_filesystem
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += boost_1_74
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    PiechartWidget.cpp \
    identifyduplicates.cpp \
    identifyduplicatespagewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    statistics.cpp

HEADERS += \
    PiechartWidget.h \
    identifyduplicates.h \
    identifyduplicatespagewidget.h \
    mainwindow.h \
    statistics.h

FORMS += \
    mainwindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


