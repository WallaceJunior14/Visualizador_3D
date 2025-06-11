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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
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
    QLabel *lblTranslacaoZ;
    QDoubleSpinBox *spinTranslacaoY;
    QLabel *lblTranslcaoY;
    QDoubleSpinBox *spinTranslacaoX;
    QLabel *lblTranslacaoX;
    QDoubleSpinBox *spinTranslacaoZ;
    QWidget *tabEscala;
    QWidget *layoutWidget_4;
    QGridLayout *gridLayout_4;
    QLabel *lblEscalaZ;
    QLabel *lblEscalaX;
    QDoubleSpinBox *spinEscalaY;
    QDoubleSpinBox *spinEscalaX;
    QLabel *lblEscalaY;
    QDoubleSpinBox *spinEscalaZ;
    QLabel *lblEscala;
    QWidget *tabRotacao;
    QWidget *layoutWidget_3;
    QGridLayout *gridLayout_3;
    QSlider *hsRotacaoX;
    QLabel *lblRotacaoY;
    QLabel *lblRotacaoZ;
    QLabel *lblRotacaoX;
    QSlider *hsRotacaoY;
    QSlider *hsRotacaoZ;
    QLabel *lblRotacao;
    QWidget *tab;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_8;
    QLabel *lblVetorNormal;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_7;
    QLabel *lblNz;
    QDoubleSpinBox *spinNz;
    QVBoxLayout *verticalLayout_5;
    QLabel *lblNx;
    QDoubleSpinBox *spinNx;
    QVBoxLayout *verticalLayout_6;
    QLabel *lblNy;
    QDoubleSpinBox *spinNy;
    QPushButton *btnCarregarOBJ;
    QComboBox *cbDisplayFile;
    QComboBox *cbDFCameras;
    QPushButton *btnLimparSelecao;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *rbTransformarObjeto;
    QRadioButton *rbTransformarCamera;
    QPushButton *btnCriarForma;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(1248, 739);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frameDesenho = new FrameDesenho(centralwidget);
        frameDesenho->setObjectName("frameDesenho");
        frameDesenho->setGeometry(QRect(270, 20, 941, 641));
        frameDesenho->setMinimumSize(QSize(600, 400));
        frameDesenho->setFrameShape(QFrame::Shape::NoFrame);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(20, 20, 231, 251));
        tabTranslacao = new QWidget();
        tabTranslacao->setObjectName("tabTranslacao");
        layoutWidget_2 = new QWidget(tabTranslacao);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(10, 20, 210, 141));
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
        lblTranslacaoZ = new QLabel(layoutWidget_2);
        lblTranslacaoZ->setObjectName("lblTranslacaoZ");

        gridLayout->addWidget(lblTranslacaoZ, 2, 0, 1, 1);

        spinTranslacaoY = new QDoubleSpinBox(layoutWidget_2);
        spinTranslacaoY->setObjectName("spinTranslacaoY");
        spinTranslacaoY->setMinimum(-100.000000000000000);
        spinTranslacaoY->setMaximum(100.000000000000000);

        gridLayout->addWidget(spinTranslacaoY, 1, 1, 1, 1);

        lblTranslcaoY = new QLabel(layoutWidget_2);
        lblTranslcaoY->setObjectName("lblTranslcaoY");

        gridLayout->addWidget(lblTranslcaoY, 0, 1, 1, 1);

        spinTranslacaoX = new QDoubleSpinBox(layoutWidget_2);
        spinTranslacaoX->setObjectName("spinTranslacaoX");
        spinTranslacaoX->setMinimum(-100.000000000000000);
        spinTranslacaoX->setMaximum(100.000000000000000);

        gridLayout->addWidget(spinTranslacaoX, 1, 0, 1, 1);

        lblTranslacaoX = new QLabel(layoutWidget_2);
        lblTranslacaoX->setObjectName("lblTranslacaoX");

        gridLayout->addWidget(lblTranslacaoX, 0, 0, 1, 1);

        spinTranslacaoZ = new QDoubleSpinBox(layoutWidget_2);
        spinTranslacaoZ->setObjectName("spinTranslacaoZ");
        spinTranslacaoZ->setMinimum(-100000.000000000000000);

        gridLayout->addWidget(spinTranslacaoZ, 3, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        tabWidget->addTab(tabTranslacao, QString());
        tabEscala = new QWidget();
        tabEscala->setObjectName("tabEscala");
        layoutWidget_4 = new QWidget(tabEscala);
        layoutWidget_4->setObjectName("layoutWidget_4");
        layoutWidget_4->setGeometry(QRect(10, 47, 201, 114));
        gridLayout_4 = new QGridLayout(layoutWidget_4);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        lblEscalaZ = new QLabel(layoutWidget_4);
        lblEscalaZ->setObjectName("lblEscalaZ");

        gridLayout_4->addWidget(lblEscalaZ, 2, 0, 1, 1);

        lblEscalaX = new QLabel(layoutWidget_4);
        lblEscalaX->setObjectName("lblEscalaX");

        gridLayout_4->addWidget(lblEscalaX, 0, 0, 1, 1);

        spinEscalaY = new QDoubleSpinBox(layoutWidget_4);
        spinEscalaY->setObjectName("spinEscalaY");
        spinEscalaY->setMinimum(-100.000000000000000);
        spinEscalaY->setMaximum(100.000000000000000);

        gridLayout_4->addWidget(spinEscalaY, 1, 1, 1, 1);

        spinEscalaX = new QDoubleSpinBox(layoutWidget_4);
        spinEscalaX->setObjectName("spinEscalaX");
        spinEscalaX->setMinimum(-100.000000000000000);
        spinEscalaX->setMaximum(100.000000000000000);

        gridLayout_4->addWidget(spinEscalaX, 1, 0, 1, 1);

        lblEscalaY = new QLabel(layoutWidget_4);
        lblEscalaY->setObjectName("lblEscalaY");

        gridLayout_4->addWidget(lblEscalaY, 0, 1, 1, 1);

        spinEscalaZ = new QDoubleSpinBox(layoutWidget_4);
        spinEscalaZ->setObjectName("spinEscalaZ");
        spinEscalaZ->setMinimum(-1000.000000000000000);

        gridLayout_4->addWidget(spinEscalaZ, 3, 0, 1, 1);

        lblEscala = new QLabel(tabEscala);
        lblEscala->setObjectName("lblEscala");
        lblEscala->setGeometry(QRect(10, 20, 199, 24));
        lblEscala->setFont(font);
        tabWidget->addTab(tabEscala, QString());
        tabRotacao = new QWidget();
        tabRotacao->setObjectName("tabRotacao");
        layoutWidget_3 = new QWidget(tabRotacao);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(10, 20, 211, 181));
        gridLayout_3 = new QGridLayout(layoutWidget_3);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        hsRotacaoX = new QSlider(layoutWidget_3);
        hsRotacaoX->setObjectName("hsRotacaoX");
        hsRotacaoX->setMinimum(-180);
        hsRotacaoX->setMaximum(180);
        hsRotacaoX->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_3->addWidget(hsRotacaoX, 3, 0, 1, 1);

        lblRotacaoY = new QLabel(layoutWidget_3);
        lblRotacaoY->setObjectName("lblRotacaoY");

        gridLayout_3->addWidget(lblRotacaoY, 4, 0, 1, 1);

        lblRotacaoZ = new QLabel(layoutWidget_3);
        lblRotacaoZ->setObjectName("lblRotacaoZ");

        gridLayout_3->addWidget(lblRotacaoZ, 6, 0, 1, 1);

        lblRotacaoX = new QLabel(layoutWidget_3);
        lblRotacaoX->setObjectName("lblRotacaoX");

        gridLayout_3->addWidget(lblRotacaoX, 2, 0, 1, 1);

        hsRotacaoY = new QSlider(layoutWidget_3);
        hsRotacaoY->setObjectName("hsRotacaoY");
        hsRotacaoY->setMinimum(-180);
        hsRotacaoY->setMaximum(180);
        hsRotacaoY->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_3->addWidget(hsRotacaoY, 5, 0, 1, 1);

        hsRotacaoZ = new QSlider(layoutWidget_3);
        hsRotacaoZ->setObjectName("hsRotacaoZ");
        hsRotacaoZ->setMinimum(-180);
        hsRotacaoZ->setMaximum(180);
        hsRotacaoZ->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_3->addWidget(hsRotacaoZ, 7, 0, 1, 1);

        lblRotacao = new QLabel(layoutWidget_3);
        lblRotacao->setObjectName("lblRotacao");
        lblRotacao->setFont(font);

        gridLayout_3->addWidget(lblRotacao, 0, 0, 2, 1);

        tabWidget->addTab(tabRotacao, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 20, 201, 145));
        verticalLayout_8 = new QVBoxLayout(layoutWidget);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        lblVetorNormal = new QLabel(layoutWidget);
        lblVetorNormal->setObjectName("lblVetorNormal");
        lblVetorNormal->setFont(font);

        verticalLayout_8->addWidget(lblVetorNormal);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        lblNz = new QLabel(layoutWidget);
        lblNz->setObjectName("lblNz");

        verticalLayout_7->addWidget(lblNz);

        spinNz = new QDoubleSpinBox(layoutWidget);
        spinNz->setObjectName("spinNz");

        verticalLayout_7->addWidget(spinNz);


        gridLayout_2->addLayout(verticalLayout_7, 2, 0, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        lblNx = new QLabel(layoutWidget);
        lblNx->setObjectName("lblNx");

        verticalLayout_5->addWidget(lblNx);

        spinNx = new QDoubleSpinBox(layoutWidget);
        spinNx->setObjectName("spinNx");

        verticalLayout_5->addWidget(spinNx);


        gridLayout_2->addLayout(verticalLayout_5, 1, 0, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        lblNy = new QLabel(layoutWidget);
        lblNy->setObjectName("lblNy");

        verticalLayout_6->addWidget(lblNy);

        spinNy = new QDoubleSpinBox(layoutWidget);
        spinNy->setObjectName("spinNy");

        verticalLayout_6->addWidget(spinNy);


        gridLayout_2->addLayout(verticalLayout_6, 1, 1, 1, 1);


        verticalLayout_8->addLayout(gridLayout_2);

        tabWidget->addTab(tab, QString());
        btnCarregarOBJ = new QPushButton(centralwidget);
        btnCarregarOBJ->setObjectName("btnCarregarOBJ");
        btnCarregarOBJ->setGeometry(QRect(1050, 680, 161, 27));
        cbDisplayFile = new QComboBox(centralwidget);
        cbDisplayFile->setObjectName("cbDisplayFile");
        cbDisplayFile->setGeometry(QRect(470, 680, 451, 28));
        cbDFCameras = new QComboBox(centralwidget);
        cbDFCameras->setObjectName("cbDFCameras");
        cbDFCameras->setGeometry(QRect(270, 680, 191, 27));
        btnLimparSelecao = new QPushButton(centralwidget);
        btnLimparSelecao->setObjectName("btnLimparSelecao");
        btnLimparSelecao->setGeometry(QRect(930, 680, 111, 27));
        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(20, 290, 231, 58));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        rbTransformarObjeto = new QRadioButton(layoutWidget1);
        rbTransformarObjeto->setObjectName("rbTransformarObjeto");

        verticalLayout_3->addWidget(rbTransformarObjeto);

        rbTransformarCamera = new QRadioButton(layoutWidget1);
        rbTransformarCamera->setObjectName("rbTransformarCamera");

        verticalLayout_3->addWidget(rbTransformarCamera);

        btnCriarForma = new QPushButton(centralwidget);
        btnCriarForma->setObjectName("btnCriarForma");
        btnCriarForma->setGeometry(QRect(20, 370, 231, 27));
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
        lblTranslacaoZ->setText(QCoreApplication::translate("MainWindow", "z", nullptr));
        lblTranslcaoY->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        lblTranslacaoX->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabTranslacao), QCoreApplication::translate("MainWindow", "T", nullptr));
        lblEscalaZ->setText(QCoreApplication::translate("MainWindow", "z", nullptr));
        lblEscalaX->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        lblEscalaY->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        lblEscala->setText(QCoreApplication::translate("MainWindow", "Escala", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabEscala), QCoreApplication::translate("MainWindow", "S", nullptr));
        lblRotacaoY->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        lblRotacaoZ->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        lblRotacaoX->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        lblRotacao->setText(QCoreApplication::translate("MainWindow", "Rota\303\247\303\243o", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabRotacao), QCoreApplication::translate("MainWindow", "R", nullptr));
        lblVetorNormal->setText(QCoreApplication::translate("MainWindow", "Vetor Normal", nullptr));
        lblNz->setText(QCoreApplication::translate("MainWindow", "Nz", nullptr));
        lblNx->setText(QCoreApplication::translate("MainWindow", "Nx", nullptr));
        lblNy->setText(QCoreApplication::translate("MainWindow", "Ny", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Vt. N", nullptr));
        btnCarregarOBJ->setText(QCoreApplication::translate("MainWindow", "Carregar Objeto", nullptr));
        btnLimparSelecao->setText(QCoreApplication::translate("MainWindow", "Limpar ", nullptr));
        rbTransformarObjeto->setText(QCoreApplication::translate("MainWindow", "Transformar objeto", nullptr));
        rbTransformarCamera->setText(QCoreApplication::translate("MainWindow", "Transformar camera", nullptr));
        btnCriarForma->setText(QCoreApplication::translate("MainWindow", "Criar Forma", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
