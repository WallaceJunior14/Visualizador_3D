/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
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
#include <QtWidgets/QGroupBox>
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
    QLabel *lblCoordenadaZ1;
    QDoubleSpinBox *spinZ1;
    QLabel *lblCoordenadaX2;
    QDoubleSpinBox *spinX2;
    QLabel *lblCoordenadaY2;
    QDoubleSpinBox *spinY2;
    QLabel *lblCoordenadaZ2;
    QDoubleSpinBox *spinZ2;
    QLabel *lblCoordenadaX3;
    QDoubleSpinBox *spinX3;
    QLabel *lblCoordenadaY3;
    QDoubleSpinBox *spinY3;
    QLabel *lblCoordenadaZ3;
    QDoubleSpinBox *spinZ3;
    QLabel *lblRaio;
    QDoubleSpinBox *spinRaio;
    QLabel *lblTamanho;
    QDoubleSpinBox *spinTamanho;
    QPushButton *btnCor;
    QPushButton *btnDesenhar;
    QPushButton *btnModificarForma;
    QPushButton *btnExcluirForma;
    QPushButton *btnCarregarOBJ;
    QComboBox *cbDisplayFile;
    QComboBox *cbDFCameras;
    QPushButton *btnLimparSelecao;
    QGroupBox *groupBoxNormal;
    QVBoxLayout *verticalLayout_4;
    QLabel *lblNx;
    QDoubleSpinBox *spinNx;
    QLabel *lblNy;
    QDoubleSpinBox *spinNy;
    QLabel *lblNz;
    QDoubleSpinBox *spinNz;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *rbTransformarObjeto;
    QRadioButton *rbTransformarCamera;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1248, 709);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frameDesenho = new FrameDesenho(centralwidget);
        frameDesenho->setObjectName(QString::fromUtf8("frameDesenho"));
        frameDesenho->setGeometry(QRect(180, 20, 800, 600));
        frameDesenho->setMinimumSize(QSize(600, 400));
        frameDesenho->setFrameShape(QFrame::NoFrame);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(1000, 20, 231, 361));
        tabTranslacao = new QWidget();
        tabTranslacao->setObjectName(QString::fromUtf8("tabTranslacao"));
        layoutWidget_2 = new QWidget(tabTranslacao);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 20, 201, 136));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lblTranslacao = new QLabel(layoutWidget_2);
        lblTranslacao->setObjectName(QString::fromUtf8("lblTranslacao"));
        QFont font;
        font.setBold(true);
        lblTranslacao->setFont(font);

        verticalLayout_2->addWidget(lblTranslacao);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lblTranslacaoZ = new QLabel(layoutWidget_2);
        lblTranslacaoZ->setObjectName(QString::fromUtf8("lblTranslacaoZ"));

        gridLayout->addWidget(lblTranslacaoZ, 2, 0, 1, 1);

        spinTranslacaoY = new QDoubleSpinBox(layoutWidget_2);
        spinTranslacaoY->setObjectName(QString::fromUtf8("spinTranslacaoY"));
        spinTranslacaoY->setMinimum(-100.000000000000000);
        spinTranslacaoY->setMaximum(100.000000000000000);

        gridLayout->addWidget(spinTranslacaoY, 1, 1, 1, 1);

        lblTranslcaoY = new QLabel(layoutWidget_2);
        lblTranslcaoY->setObjectName(QString::fromUtf8("lblTranslcaoY"));

        gridLayout->addWidget(lblTranslcaoY, 0, 1, 1, 1);

        spinTranslacaoX = new QDoubleSpinBox(layoutWidget_2);
        spinTranslacaoX->setObjectName(QString::fromUtf8("spinTranslacaoX"));
        spinTranslacaoX->setMinimum(-100.000000000000000);
        spinTranslacaoX->setMaximum(100.000000000000000);

        gridLayout->addWidget(spinTranslacaoX, 1, 0, 1, 1);

        lblTranslacaoX = new QLabel(layoutWidget_2);
        lblTranslacaoX->setObjectName(QString::fromUtf8("lblTranslacaoX"));

        gridLayout->addWidget(lblTranslacaoX, 0, 0, 1, 1);

        spinTranslacaoZ = new QDoubleSpinBox(layoutWidget_2);
        spinTranslacaoZ->setObjectName(QString::fromUtf8("spinTranslacaoZ"));

        gridLayout->addWidget(spinTranslacaoZ, 3, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        tabWidget->addTab(tabTranslacao, QString());
        tabEscala = new QWidget();
        tabEscala->setObjectName(QString::fromUtf8("tabEscala"));
        layoutWidget_4 = new QWidget(tabEscala);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(10, 47, 201, 110));
        gridLayout_4 = new QGridLayout(layoutWidget_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        lblEscalaZ = new QLabel(layoutWidget_4);
        lblEscalaZ->setObjectName(QString::fromUtf8("lblEscalaZ"));

        gridLayout_4->addWidget(lblEscalaZ, 2, 0, 1, 1);

        lblEscalaX = new QLabel(layoutWidget_4);
        lblEscalaX->setObjectName(QString::fromUtf8("lblEscalaX"));

        gridLayout_4->addWidget(lblEscalaX, 0, 0, 1, 1);

        spinEscalaY = new QDoubleSpinBox(layoutWidget_4);
        spinEscalaY->setObjectName(QString::fromUtf8("spinEscalaY"));
        spinEscalaY->setMinimum(-100.000000000000000);
        spinEscalaY->setMaximum(100.000000000000000);

        gridLayout_4->addWidget(spinEscalaY, 1, 1, 1, 1);

        spinEscalaX = new QDoubleSpinBox(layoutWidget_4);
        spinEscalaX->setObjectName(QString::fromUtf8("spinEscalaX"));
        spinEscalaX->setMinimum(-100.000000000000000);
        spinEscalaX->setMaximum(100.000000000000000);

        gridLayout_4->addWidget(spinEscalaX, 1, 0, 1, 1);

        lblEscalaY = new QLabel(layoutWidget_4);
        lblEscalaY->setObjectName(QString::fromUtf8("lblEscalaY"));

        gridLayout_4->addWidget(lblEscalaY, 0, 1, 1, 1);

        spinEscalaZ = new QDoubleSpinBox(layoutWidget_4);
        spinEscalaZ->setObjectName(QString::fromUtf8("spinEscalaZ"));

        gridLayout_4->addWidget(spinEscalaZ, 3, 0, 1, 1);

        lblEscala = new QLabel(tabEscala);
        lblEscala->setObjectName(QString::fromUtf8("lblEscala"));
        lblEscala->setGeometry(QRect(10, 20, 199, 24));
        lblEscala->setFont(font);
        tabWidget->addTab(tabEscala, QString());
        tabRotacao = new QWidget();
        tabRotacao->setObjectName(QString::fromUtf8("tabRotacao"));
        layoutWidget_3 = new QWidget(tabRotacao);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 20, 211, 290));
        gridLayout_3 = new QGridLayout(layoutWidget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        hsRotacaoZ = new QSlider(layoutWidget_3);
        hsRotacaoZ->setObjectName(QString::fromUtf8("hsRotacaoZ"));
        hsRotacaoZ->setEnabled(false);
        hsRotacaoZ->setMinimum(-180);
        hsRotacaoZ->setMaximum(180);

        gridLayout_3->addWidget(hsRotacaoZ, 4, 1, 1, 1);

        lblRotacaoZ = new QLabel(layoutWidget_3);
        lblRotacaoZ->setObjectName(QString::fromUtf8("lblRotacaoZ"));

        gridLayout_3->addWidget(lblRotacaoZ, 4, 0, 1, 1);

        hsRotacaoX = new QSlider(layoutWidget_3);
        hsRotacaoX->setObjectName(QString::fromUtf8("hsRotacaoX"));
        hsRotacaoX->setMinimum(-180);
        hsRotacaoX->setMaximum(180);

        gridLayout_3->addWidget(hsRotacaoX, 2, 1, 1, 1);

        lblRotacaoY = new QLabel(layoutWidget_3);
        lblRotacaoY->setObjectName(QString::fromUtf8("lblRotacaoY"));

        gridLayout_3->addWidget(lblRotacaoY, 3, 0, 1, 1);

        hsRotacaoY = new QSlider(layoutWidget_3);
        hsRotacaoY->setObjectName(QString::fromUtf8("hsRotacaoY"));
        hsRotacaoY->setMinimum(-180);
        hsRotacaoY->setMaximum(180);

        gridLayout_3->addWidget(hsRotacaoY, 3, 1, 1, 1);

        lblRotacaoX = new QLabel(layoutWidget_3);
        lblRotacaoX->setObjectName(QString::fromUtf8("lblRotacaoX"));

        gridLayout_3->addWidget(lblRotacaoX, 2, 0, 1, 1);

        lblRotacao = new QLabel(layoutWidget_3);
        lblRotacao->setObjectName(QString::fromUtf8("lblRotacao"));
        lblRotacao->setFont(font);

        gridLayout_3->addWidget(lblRotacao, 1, 1, 1, 1);

        tabWidget->addTab(tabRotacao, QString());
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 131, 681));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblForma = new QLabel(layoutWidget);
        lblForma->setObjectName(QString::fromUtf8("lblForma"));

        verticalLayout->addWidget(lblForma);

        comboFormas = new QComboBox(layoutWidget);
        comboFormas->setObjectName(QString::fromUtf8("comboFormas"));

        verticalLayout->addWidget(comboFormas);

        lblCoordenadaX1 = new QLabel(layoutWidget);
        lblCoordenadaX1->setObjectName(QString::fromUtf8("lblCoordenadaX1"));

        verticalLayout->addWidget(lblCoordenadaX1);

        spinX1 = new QDoubleSpinBox(layoutWidget);
        spinX1->setObjectName(QString::fromUtf8("spinX1"));
        spinX1->setMaximum(600.000000000000000);

        verticalLayout->addWidget(spinX1);

        lblCoordenadaY1 = new QLabel(layoutWidget);
        lblCoordenadaY1->setObjectName(QString::fromUtf8("lblCoordenadaY1"));

        verticalLayout->addWidget(lblCoordenadaY1);

        spinY1 = new QDoubleSpinBox(layoutWidget);
        spinY1->setObjectName(QString::fromUtf8("spinY1"));
        spinY1->setMaximum(600.000000000000000);

        verticalLayout->addWidget(spinY1);

        lblCoordenadaZ1 = new QLabel(layoutWidget);
        lblCoordenadaZ1->setObjectName(QString::fromUtf8("lblCoordenadaZ1"));

        verticalLayout->addWidget(lblCoordenadaZ1);

        spinZ1 = new QDoubleSpinBox(layoutWidget);
        spinZ1->setObjectName(QString::fromUtf8("spinZ1"));

        verticalLayout->addWidget(spinZ1);

        lblCoordenadaX2 = new QLabel(layoutWidget);
        lblCoordenadaX2->setObjectName(QString::fromUtf8("lblCoordenadaX2"));

        verticalLayout->addWidget(lblCoordenadaX2);

        spinX2 = new QDoubleSpinBox(layoutWidget);
        spinX2->setObjectName(QString::fromUtf8("spinX2"));
        spinX2->setMaximum(600.000000000000000);

        verticalLayout->addWidget(spinX2);

        lblCoordenadaY2 = new QLabel(layoutWidget);
        lblCoordenadaY2->setObjectName(QString::fromUtf8("lblCoordenadaY2"));

        verticalLayout->addWidget(lblCoordenadaY2);

        spinY2 = new QDoubleSpinBox(layoutWidget);
        spinY2->setObjectName(QString::fromUtf8("spinY2"));
        spinY2->setMaximum(600.000000000000000);

        verticalLayout->addWidget(spinY2);

        lblCoordenadaZ2 = new QLabel(layoutWidget);
        lblCoordenadaZ2->setObjectName(QString::fromUtf8("lblCoordenadaZ2"));

        verticalLayout->addWidget(lblCoordenadaZ2);

        spinZ2 = new QDoubleSpinBox(layoutWidget);
        spinZ2->setObjectName(QString::fromUtf8("spinZ2"));

        verticalLayout->addWidget(spinZ2);

        lblCoordenadaX3 = new QLabel(layoutWidget);
        lblCoordenadaX3->setObjectName(QString::fromUtf8("lblCoordenadaX3"));
        lblCoordenadaX3->setEnabled(true);

        verticalLayout->addWidget(lblCoordenadaX3);

        spinX3 = new QDoubleSpinBox(layoutWidget);
        spinX3->setObjectName(QString::fromUtf8("spinX3"));
        spinX3->setMaximum(600.000000000000000);

        verticalLayout->addWidget(spinX3);

        lblCoordenadaY3 = new QLabel(layoutWidget);
        lblCoordenadaY3->setObjectName(QString::fromUtf8("lblCoordenadaY3"));
        lblCoordenadaY3->setEnabled(true);

        verticalLayout->addWidget(lblCoordenadaY3);

        spinY3 = new QDoubleSpinBox(layoutWidget);
        spinY3->setObjectName(QString::fromUtf8("spinY3"));
        spinY3->setMaximum(600.000000000000000);

        verticalLayout->addWidget(spinY3);

        lblCoordenadaZ3 = new QLabel(layoutWidget);
        lblCoordenadaZ3->setObjectName(QString::fromUtf8("lblCoordenadaZ3"));

        verticalLayout->addWidget(lblCoordenadaZ3);

        spinZ3 = new QDoubleSpinBox(layoutWidget);
        spinZ3->setObjectName(QString::fromUtf8("spinZ3"));

        verticalLayout->addWidget(spinZ3);

        lblRaio = new QLabel(layoutWidget);
        lblRaio->setObjectName(QString::fromUtf8("lblRaio"));

        verticalLayout->addWidget(lblRaio);

        spinRaio = new QDoubleSpinBox(layoutWidget);
        spinRaio->setObjectName(QString::fromUtf8("spinRaio"));
        spinRaio->setMaximum(100.000000000000000);

        verticalLayout->addWidget(spinRaio);

        lblTamanho = new QLabel(layoutWidget);
        lblTamanho->setObjectName(QString::fromUtf8("lblTamanho"));

        verticalLayout->addWidget(lblTamanho);

        spinTamanho = new QDoubleSpinBox(layoutWidget);
        spinTamanho->setObjectName(QString::fromUtf8("spinTamanho"));

        verticalLayout->addWidget(spinTamanho);

        btnCor = new QPushButton(layoutWidget);
        btnCor->setObjectName(QString::fromUtf8("btnCor"));

        verticalLayout->addWidget(btnCor);

        btnDesenhar = new QPushButton(layoutWidget);
        btnDesenhar->setObjectName(QString::fromUtf8("btnDesenhar"));

        verticalLayout->addWidget(btnDesenhar);

        btnModificarForma = new QPushButton(layoutWidget);
        btnModificarForma->setObjectName(QString::fromUtf8("btnModificarForma"));

        verticalLayout->addWidget(btnModificarForma);

        btnExcluirForma = new QPushButton(layoutWidget);
        btnExcluirForma->setObjectName(QString::fromUtf8("btnExcluirForma"));

        verticalLayout->addWidget(btnExcluirForma);

        btnCarregarOBJ = new QPushButton(centralwidget);
        btnCarregarOBJ->setObjectName(QString::fromUtf8("btnCarregarOBJ"));
        btnCarregarOBJ->setGeometry(QRect(1130, 640, 101, 27));
        cbDisplayFile = new QComboBox(centralwidget);
        cbDisplayFile->setObjectName(QString::fromUtf8("cbDisplayFile"));
        cbDisplayFile->setGeometry(QRect(380, 640, 481, 28));
        cbDFCameras = new QComboBox(centralwidget);
        cbDFCameras->setObjectName(QString::fromUtf8("cbDFCameras"));
        cbDFCameras->setGeometry(QRect(180, 640, 191, 27));
        btnLimparSelecao = new QPushButton(centralwidget);
        btnLimparSelecao->setObjectName(QString::fromUtf8("btnLimparSelecao"));
        btnLimparSelecao->setGeometry(QRect(870, 640, 111, 27));
        groupBoxNormal = new QGroupBox(centralwidget);
        groupBoxNormal->setObjectName(QString::fromUtf8("groupBoxNormal"));
        groupBoxNormal->setGeometry(QRect(1020, 480, 89, 191));
        verticalLayout_4 = new QVBoxLayout(groupBoxNormal);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        lblNx = new QLabel(groupBoxNormal);
        lblNx->setObjectName(QString::fromUtf8("lblNx"));

        verticalLayout_4->addWidget(lblNx);

        spinNx = new QDoubleSpinBox(groupBoxNormal);
        spinNx->setObjectName(QString::fromUtf8("spinNx"));

        verticalLayout_4->addWidget(spinNx);

        lblNy = new QLabel(groupBoxNormal);
        lblNy->setObjectName(QString::fromUtf8("lblNy"));

        verticalLayout_4->addWidget(lblNy);

        spinNy = new QDoubleSpinBox(groupBoxNormal);
        spinNy->setObjectName(QString::fromUtf8("spinNy"));

        verticalLayout_4->addWidget(spinNy);

        lblNz = new QLabel(groupBoxNormal);
        lblNz->setObjectName(QString::fromUtf8("lblNz"));

        verticalLayout_4->addWidget(lblNz);

        spinNz = new QDoubleSpinBox(groupBoxNormal);
        spinNz->setObjectName(QString::fromUtf8("spinNz"));

        verticalLayout_4->addWidget(spinNz);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(1010, 410, 163, 56));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        rbTransformarObjeto = new QRadioButton(layoutWidget1);
        rbTransformarObjeto->setObjectName(QString::fromUtf8("rbTransformarObjeto"));

        verticalLayout_3->addWidget(rbTransformarObjeto);

        rbTransformarCamera = new QRadioButton(layoutWidget1);
        rbTransformarCamera->setObjectName(QString::fromUtf8("rbTransformarCamera"));

        verticalLayout_3->addWidget(rbTransformarCamera);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


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
        lblRotacaoZ->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        lblRotacaoY->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        lblRotacaoX->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        lblRotacao->setText(QCoreApplication::translate("MainWindow", "Rota\303\247\303\243o", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabRotacao), QCoreApplication::translate("MainWindow", "R", nullptr));
        lblForma->setText(QCoreApplication::translate("MainWindow", "Forma:", nullptr));
        lblCoordenadaX1->setText(QCoreApplication::translate("MainWindow", "Coordenada X1:", nullptr));
        lblCoordenadaY1->setText(QCoreApplication::translate("MainWindow", "Coodernada Y1:", nullptr));
        lblCoordenadaZ1->setText(QCoreApplication::translate("MainWindow", "Coordenada Z1:", nullptr));
        lblCoordenadaX2->setText(QCoreApplication::translate("MainWindow", "Coordenada X2:", nullptr));
        lblCoordenadaY2->setText(QCoreApplication::translate("MainWindow", "Coodernada Y2:", nullptr));
        lblCoordenadaZ2->setText(QCoreApplication::translate("MainWindow", "Coordenada Z2:", nullptr));
        lblCoordenadaX3->setText(QCoreApplication::translate("MainWindow", "Coordenada X3:", nullptr));
        lblCoordenadaY3->setText(QCoreApplication::translate("MainWindow", "Coordenada Y3:", nullptr));
        lblCoordenadaZ3->setText(QCoreApplication::translate("MainWindow", "Coordenada Z3:", nullptr));
        lblRaio->setText(QCoreApplication::translate("MainWindow", "Raio:", nullptr));
        lblTamanho->setText(QCoreApplication::translate("MainWindow", "Tamanho", nullptr));
        btnCor->setText(QCoreApplication::translate("MainWindow", "Selecionar Cor", nullptr));
        btnDesenhar->setText(QCoreApplication::translate("MainWindow", "Adicionar", nullptr));
        btnModificarForma->setText(QCoreApplication::translate("MainWindow", "Modificar", nullptr));
        btnExcluirForma->setText(QCoreApplication::translate("MainWindow", "Excluir", nullptr));
        btnCarregarOBJ->setText(QCoreApplication::translate("MainWindow", "Carregar", nullptr));
        btnLimparSelecao->setText(QCoreApplication::translate("MainWindow", "Limpar Sele\303\247\303\243o", nullptr));
        groupBoxNormal->setTitle(QCoreApplication::translate("MainWindow", "Vetor Normal", nullptr));
        lblNx->setText(QCoreApplication::translate("MainWindow", "Nx", nullptr));
        lblNy->setText(QCoreApplication::translate("MainWindow", "Ny", nullptr));
        lblNz->setText(QCoreApplication::translate("MainWindow", "Nz", nullptr));
        rbTransformarObjeto->setText(QCoreApplication::translate("MainWindow", "Transformar objeto", nullptr));
        rbTransformarCamera->setText(QCoreApplication::translate("MainWindow", "Transformar camera", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
