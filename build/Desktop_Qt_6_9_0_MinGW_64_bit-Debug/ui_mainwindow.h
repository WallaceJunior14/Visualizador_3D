/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "frame_desenho.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    FrameDesenho *frameDesenho;
    QTabWidget *tabWidget;
    QWidget *tabTranslacao;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblTranslacao;
    QGridLayout *gridLayout;
    QLabel *lblTranslacaoX;
    QLabel *lblTranslcaoY;
    QDoubleSpinBox *spinTranslacaoX;
    QDoubleSpinBox *spinTranslacaoY;
    QWidget *tabEscala;
    QWidget *layoutWidget_4;
    QGridLayout *gridLayout_4;
    QLabel *lblEscalaY;
    QDoubleSpinBox *spinEscalaX;
    QDoubleSpinBox *spinEscalaY;
    QLabel *lblEscalaX;
    QLabel *lblEscala;
    QWidget *tabRotacao;
    QWidget *layoutWidget_3;
    QGridLayout *gridLayout_3;
    QSlider *hsRotacaoZ;
    QLabel *lblRotacaoZ;
    QSlider *hsRotacaoX;
    QLabel *lblRotacaoY;
    QSlider *hsRotacaoY;
    QLabel *lblRotacaoX;
    QLabel *lblRotacao;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lblForma;
    QComboBox *comboFormas;
    QLabel *lblCoordenadaX1;
    QDoubleSpinBox *spinX1;
    QLabel *lblCoordenadaY1;
    QDoubleSpinBox *spinY1;
    QLabel *lblCoordenadaX2;
    QDoubleSpinBox *spinX2;
    QLabel *lblCoordenadaY2;
    QDoubleSpinBox *spinY2;
    QLabel *lblCoordenadaX3;
    QDoubleSpinBox *spinX3;
    QLabel *lblCoordenadaY3;
    QDoubleSpinBox *spinY3;
    QLabel *lblRaio;
    QDoubleSpinBox *spinRaio;
    QPushButton *btnCor;
    QPushButton *btnDesenhar;
    QPushButton *btnModificarForma;
    QPushButton *btnExcluirForma;
    QPushButton *btnCarregarOBJ;
    QComboBox *cbDisplayFile;
    QComboBox *cbDFCameras;
    QPushButton *btnLimparSelecao;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(1248, 709);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frameDesenho = new FrameDesenho(centralwidget);
        frameDesenho->setObjectName("frameDesenho");
        frameDesenho->setGeometry(QRect(180, 20, 800, 600));
        frameDesenho->setMinimumSize(QSize(600, 400));
        frameDesenho->setFrameShape(QFrame::Shape::StyledPanel);
        frameDesenho->setFrameShadow(QFrame::Shadow::Raised);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(1000, 20, 231, 171));
        tabTranslacao = new QWidget();
        tabTranslacao->setObjectName("tabTranslacao");
        layoutWidget_2 = new QWidget(tabTranslacao);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(10, 20, 201, 91));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lblTranslacao = new QLabel(layoutWidget_2);
        lblTranslacao->setObjectName("lblTranslacao");
        QFont font;
        font.setBold(true);
        lblTranslacao->setFont(font);

        verticalLayout_2->addWidget(lblTranslacao);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        lblTranslacaoX = new QLabel(layoutWidget_2);
        lblTranslacaoX->setObjectName("lblTranslacaoX");

        gridLayout->addWidget(lblTranslacaoX, 0, 0, 1, 1);

        lblTranslcaoY = new QLabel(layoutWidget_2);
        lblTranslcaoY->setObjectName("lblTranslcaoY");

        gridLayout->addWidget(lblTranslcaoY, 0, 1, 1, 1);

        spinTranslacaoX = new QDoubleSpinBox(layoutWidget_2);
        spinTranslacaoX->setObjectName("spinTranslacaoX");
        spinTranslacaoX->setMinimum(-100.000000000000000);
        spinTranslacaoX->setMaximum(100.000000000000000);

        gridLayout->addWidget(spinTranslacaoX, 1, 0, 1, 1);

        spinTranslacaoY = new QDoubleSpinBox(layoutWidget_2);
        spinTranslacaoY->setObjectName("spinTranslacaoY");
        spinTranslacaoY->setMinimum(-100.000000000000000);
        spinTranslacaoY->setMaximum(100.000000000000000);

        gridLayout->addWidget(spinTranslacaoY, 1, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        tabWidget->addTab(tabTranslacao, QString());
        tabEscala = new QWidget();
        tabEscala->setObjectName("tabEscala");
        layoutWidget_4 = new QWidget(tabEscala);
        layoutWidget_4->setObjectName("layoutWidget_4");
        layoutWidget_4->setGeometry(QRect(10, 47, 201, 61));
        gridLayout_4 = new QGridLayout(layoutWidget_4);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        lblEscalaY = new QLabel(layoutWidget_4);
        lblEscalaY->setObjectName("lblEscalaY");

        gridLayout_4->addWidget(lblEscalaY, 0, 1, 1, 1);

        spinEscalaX = new QDoubleSpinBox(layoutWidget_4);
        spinEscalaX->setObjectName("spinEscalaX");
        spinEscalaX->setMinimum(-100.000000000000000);
        spinEscalaX->setMaximum(100.000000000000000);

        gridLayout_4->addWidget(spinEscalaX, 1, 0, 1, 1);

        spinEscalaY = new QDoubleSpinBox(layoutWidget_4);
        spinEscalaY->setObjectName("spinEscalaY");
        spinEscalaY->setMinimum(-100.000000000000000);
        spinEscalaY->setMaximum(100.000000000000000);

        gridLayout_4->addWidget(spinEscalaY, 1, 1, 1, 1);

        lblEscalaX = new QLabel(layoutWidget_4);
        lblEscalaX->setObjectName("lblEscalaX");

        gridLayout_4->addWidget(lblEscalaX, 0, 0, 1, 1);

        lblEscala = new QLabel(tabEscala);
        lblEscala->setObjectName("lblEscala");
        lblEscala->setGeometry(QRect(10, 20, 199, 24));
        lblEscala->setFont(font);
        tabWidget->addTab(tabEscala, QString());
        tabRotacao = new QWidget();
        tabRotacao->setObjectName("tabRotacao");
        layoutWidget_3 = new QWidget(tabRotacao);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(10, 20, 211, 103));
        gridLayout_3 = new QGridLayout(layoutWidget_3);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        hsRotacaoZ = new QSlider(layoutWidget_3);
        hsRotacaoZ->setObjectName("hsRotacaoZ");
        hsRotacaoZ->setEnabled(false);
        hsRotacaoZ->setMinimum(-180);
        hsRotacaoZ->setMaximum(180);
        hsRotacaoZ->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_3->addWidget(hsRotacaoZ, 4, 1, 1, 1);

        lblRotacaoZ = new QLabel(layoutWidget_3);
        lblRotacaoZ->setObjectName("lblRotacaoZ");

        gridLayout_3->addWidget(lblRotacaoZ, 4, 0, 1, 1);

        hsRotacaoX = new QSlider(layoutWidget_3);
        hsRotacaoX->setObjectName("hsRotacaoX");
        hsRotacaoX->setMinimum(-180);
        hsRotacaoX->setMaximum(180);
        hsRotacaoX->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_3->addWidget(hsRotacaoX, 2, 1, 1, 1);

        lblRotacaoY = new QLabel(layoutWidget_3);
        lblRotacaoY->setObjectName("lblRotacaoY");

        gridLayout_3->addWidget(lblRotacaoY, 3, 0, 1, 1);

        hsRotacaoY = new QSlider(layoutWidget_3);
        hsRotacaoY->setObjectName("hsRotacaoY");
        hsRotacaoY->setMinimum(-180);
        hsRotacaoY->setMaximum(180);
        hsRotacaoY->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_3->addWidget(hsRotacaoY, 3, 1, 1, 1);

        lblRotacaoX = new QLabel(layoutWidget_3);
        lblRotacaoX->setObjectName("lblRotacaoX");

        gridLayout_3->addWidget(lblRotacaoX, 2, 0, 1, 1);

        lblRotacao = new QLabel(layoutWidget_3);
        lblRotacao->setObjectName("lblRotacao");
        lblRotacao->setFont(font);

        gridLayout_3->addWidget(lblRotacao, 1, 1, 1, 1);

        tabWidget->addTab(tabRotacao, QString());
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 20, 141, 651));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblForma = new QLabel(layoutWidget);
        lblForma->setObjectName("lblForma");

        verticalLayout->addWidget(lblForma);

        comboFormas = new QComboBox(layoutWidget);
        comboFormas->setObjectName("comboFormas");

        verticalLayout->addWidget(comboFormas);

        lblCoordenadaX1 = new QLabel(layoutWidget);
        lblCoordenadaX1->setObjectName("lblCoordenadaX1");

        verticalLayout->addWidget(lblCoordenadaX1);

        spinX1 = new QDoubleSpinBox(layoutWidget);
        spinX1->setObjectName("spinX1");
        spinX1->setMaximum(600.000000000000000);

        verticalLayout->addWidget(spinX1);

        lblCoordenadaY1 = new QLabel(layoutWidget);
        lblCoordenadaY1->setObjectName("lblCoordenadaY1");

        verticalLayout->addWidget(lblCoordenadaY1);

        spinY1 = new QDoubleSpinBox(layoutWidget);
        spinY1->setObjectName("spinY1");
        spinY1->setMaximum(600.000000000000000);

        verticalLayout->addWidget(spinY1);

        lblCoordenadaX2 = new QLabel(layoutWidget);
        lblCoordenadaX2->setObjectName("lblCoordenadaX2");

        verticalLayout->addWidget(lblCoordenadaX2);

        spinX2 = new QDoubleSpinBox(layoutWidget);
        spinX2->setObjectName("spinX2");
        spinX2->setMaximum(600.000000000000000);

        verticalLayout->addWidget(spinX2);

        lblCoordenadaY2 = new QLabel(layoutWidget);
        lblCoordenadaY2->setObjectName("lblCoordenadaY2");

        verticalLayout->addWidget(lblCoordenadaY2);

        spinY2 = new QDoubleSpinBox(layoutWidget);
        spinY2->setObjectName("spinY2");
        spinY2->setMaximum(600.000000000000000);

        verticalLayout->addWidget(spinY2);

        lblCoordenadaX3 = new QLabel(layoutWidget);
        lblCoordenadaX3->setObjectName("lblCoordenadaX3");
        lblCoordenadaX3->setEnabled(true);

        verticalLayout->addWidget(lblCoordenadaX3);

        spinX3 = new QDoubleSpinBox(layoutWidget);
        spinX3->setObjectName("spinX3");
        spinX3->setMaximum(600.000000000000000);

        verticalLayout->addWidget(spinX3);

        lblCoordenadaY3 = new QLabel(layoutWidget);
        lblCoordenadaY3->setObjectName("lblCoordenadaY3");
        lblCoordenadaY3->setEnabled(true);

        verticalLayout->addWidget(lblCoordenadaY3);

        spinY3 = new QDoubleSpinBox(layoutWidget);
        spinY3->setObjectName("spinY3");
        spinY3->setMaximum(600.000000000000000);

        verticalLayout->addWidget(spinY3);

        lblRaio = new QLabel(layoutWidget);
        lblRaio->setObjectName("lblRaio");

        verticalLayout->addWidget(lblRaio);

        spinRaio = new QDoubleSpinBox(layoutWidget);
        spinRaio->setObjectName("spinRaio");
        spinRaio->setMaximum(100.000000000000000);

        verticalLayout->addWidget(spinRaio);

        btnCor = new QPushButton(layoutWidget);
        btnCor->setObjectName("btnCor");

        verticalLayout->addWidget(btnCor);

        btnDesenhar = new QPushButton(layoutWidget);
        btnDesenhar->setObjectName("btnDesenhar");

        verticalLayout->addWidget(btnDesenhar);

        btnModificarForma = new QPushButton(layoutWidget);
        btnModificarForma->setObjectName("btnModificarForma");

        verticalLayout->addWidget(btnModificarForma);

        btnExcluirForma = new QPushButton(layoutWidget);
        btnExcluirForma->setObjectName("btnExcluirForma");

        verticalLayout->addWidget(btnExcluirForma);

        btnCarregarOBJ = new QPushButton(centralwidget);
        btnCarregarOBJ->setObjectName("btnCarregarOBJ");
        btnCarregarOBJ->setGeometry(QRect(1130, 640, 101, 27));
        cbDisplayFile = new QComboBox(centralwidget);
        cbDisplayFile->setObjectName("cbDisplayFile");
        cbDisplayFile->setGeometry(QRect(380, 640, 481, 28));
        cbDFCameras = new QComboBox(centralwidget);
        cbDFCameras->setObjectName("cbDFCameras");
        cbDFCameras->setGeometry(QRect(180, 640, 191, 27));
        btnLimparSelecao = new QPushButton(centralwidget);
        btnLimparSelecao->setObjectName("btnLimparSelecao");
        btnLimparSelecao->setGeometry(QRect(870, 640, 111, 27));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Vizualizador 3D", nullptr));
        lblTranslacao->setText(QCoreApplication::translate("MainWindow", "Transla\303\247\303\243o", nullptr));
        lblTranslacaoX->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        lblTranslcaoY->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabTranslacao), QCoreApplication::translate("MainWindow", "T", nullptr));
        lblEscalaY->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        lblEscalaX->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        lblEscala->setText(QCoreApplication::translate("MainWindow", "Escala", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabEscala), QCoreApplication::translate("MainWindow", "S", nullptr));
        lblRotacaoZ->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        lblRotacaoY->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        lblRotacaoX->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        lblRotacao->setText(QCoreApplication::translate("MainWindow", "Rota\303\247\303\243o", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabRotacao), QCoreApplication::translate("MainWindow", "R", nullptr));
        lblForma->setText(QCoreApplication::translate("MainWindow", "Forma:", nullptr));
        lblCoordenadaX1->setText(QCoreApplication::translate("MainWindow", "Coordenada X1:", nullptr));
        lblCoordenadaY1->setText(QCoreApplication::translate("MainWindow", "Coodernada Y1:", nullptr));
        lblCoordenadaX2->setText(QCoreApplication::translate("MainWindow", "Coordenada X2:", nullptr));
        lblCoordenadaY2->setText(QCoreApplication::translate("MainWindow", "Coodernada Y2:", nullptr));
        lblCoordenadaX3->setText(QCoreApplication::translate("MainWindow", "Coordenada X3:", nullptr));
        lblCoordenadaY3->setText(QCoreApplication::translate("MainWindow", "Coordenada Y3:", nullptr));
        lblRaio->setText(QCoreApplication::translate("MainWindow", "Raio:", nullptr));
        btnCor->setText(QCoreApplication::translate("MainWindow", "Selecionar Cor", nullptr));
        btnDesenhar->setText(QCoreApplication::translate("MainWindow", "Adicionar", nullptr));
        btnModificarForma->setText(QCoreApplication::translate("MainWindow", "Modificar", nullptr));
        btnExcluirForma->setText(QCoreApplication::translate("MainWindow", "Excluir", nullptr));
        btnCarregarOBJ->setText(QCoreApplication::translate("MainWindow", "Carregar", nullptr));
        btnLimparSelecao->setText(QCoreApplication::translate("MainWindow", "Limpar Sele\303\247\303\243o", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
