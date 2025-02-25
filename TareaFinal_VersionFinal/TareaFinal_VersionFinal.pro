TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    Logica/logica.c \
    Interfaz/interfaz.c \
    Menu/menu.c

HEADERS += \
    Logica/Logica.h \
    Menu/menu.h \
    Interfaz/interfaz.h \
    Logica/datos.h

