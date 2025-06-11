QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bounding_box.cpp \
    camera.cpp \
    carregador_obj.cpp \
    circunferencia_obj.cpp \
    clipper.cpp \
    display_file.cpp \
    frame_desenho.cpp \
    gerenciadorobjetosdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    malha_obj.cpp \
    matriz.cpp \
    objeto_grafico.cpp \
    poligono_obj.cpp \
    ponto2d.cpp \
    ponto3d.cpp \
    ponto_obj.cpp \
    reta_obj.cpp \
    transformador_geometrico.cpp \
    viewport_tela.cpp

HEADERS += \
    bounding_box.h \
    camera.h \
    carregador_obj.h \
    circunferencia_obj.h \
    clipper.h \
    display_file.h \
    frame_desenho.h \
    gerenciadorobjetosdialog.h \
    mainwindow.h \
    malha_obj.h \
    matriz.h \
    objeto_grafico.h \
    poligono_obj.h \
    ponto2d.h \
    ponto3d.h \
    ponto_obj.h \
    reta_obj.h \
    tipos.h \
    transformador_geometrico.h \
    viewport_tela.h

FORMS += \
    gerenciadorobjetosdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
