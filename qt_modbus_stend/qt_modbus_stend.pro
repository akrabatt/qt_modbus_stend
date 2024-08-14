QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    libmodbus/modbus-data.c \
    libmodbus/modbus-rtu.c \
    libmodbus/modbus-tcp.c \
    libmodbus/modbus.c \
    main.cpp \
    modbus_funct/0x03.cpp \
    stend_main_window.cpp

HEADERS += \
    libmodbus/config.h \
    libmodbus/modbus-private.h \
    libmodbus/modbus-rtu-private.h \
    libmodbus/modbus-rtu.h \
    libmodbus/modbus-tcp-private.h \
    libmodbus/modbus-tcp.h \
    libmodbus/modbus-version.h \
    libmodbus/modbus.h \
    modbus_funct/0x03.h \
    stend_main_window.h

FORMS += \
    stend_main_window.ui

TRANSLATIONS += \
    qt_modbus_stend_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
