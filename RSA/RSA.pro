QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    filecr.cpp \
    main.cpp \
    mainwindow.cpp \
    rsa_encrypt_decrypt.cpp \
    rsa_keycreator.cpp \
    rsa_keysaver.cpp

HEADERS += \
    filecr.h \
    mainwindow.h \
    rsa_encrypt_decrypt.h \
    rsa_keycreator.h \
    rsa_keysaver.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/res.qrc
