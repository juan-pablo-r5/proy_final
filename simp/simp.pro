QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dona.cpp \
    ecenario.cpp \
    enemigo.cpp \
    main.cpp \
    meteor.cpp \
    personaje.cpp \
    reglas_juego.cpp \
    sprite.cpp \
    ventanas.cpp

HEADERS += \
    dona.h \
    ecenario.h \
    enemigo.h \
    meteor.h \
    personaje.h \
    reglas_juego.h \
    sprite.h \
    ventanas.h

FORMS += \
    ventanas.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imagenes.qrc
