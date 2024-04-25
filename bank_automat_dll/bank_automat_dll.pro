QT += gui \
    widgets
QT += serialport

TEMPLATE = lib
DEFINES += BANK_AUTOMAT_DLL_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bank_automat_dll.cpp

HEADERS += \
    bank_automat_dll_global.h \
    bank_automat_dll.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS +=
