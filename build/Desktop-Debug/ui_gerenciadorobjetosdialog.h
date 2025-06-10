/********************************************************************************
** Form generated from reading UI file 'gerenciadorobjetosdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GERENCIADOROBJETOSDIALOG_H
#define UI_GERENCIADOROBJETOSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GerenciadorObjetosDialog
{
public:
    QDialogButtonBox *buttonBox;
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

    void setupUi(QDialog *GerenciadorObjetosDialog)
    {
        if (GerenciadorObjetosDialog->objectName().isEmpty())
            GerenciadorObjetosDialog->setObjectName("GerenciadorObjetosDialog");
        GerenciadorObjetosDialog->resize(788, 859);
        buttonBox = new QDialogButtonBox(GerenciadorObjetosDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(430, 450, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        layoutWidget = new QWidget(GerenciadorObjetosDialog);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(40, 0, 131, 835));
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

        lblCoordenadaZ1 = new QLabel(layoutWidget);
        lblCoordenadaZ1->setObjectName("lblCoordenadaZ1");

        verticalLayout->addWidget(lblCoordenadaZ1);

        spinZ1 = new QDoubleSpinBox(layoutWidget);
        spinZ1->setObjectName("spinZ1");

        verticalLayout->addWidget(spinZ1);

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

        lblCoordenadaZ2 = new QLabel(layoutWidget);
        lblCoordenadaZ2->setObjectName("lblCoordenadaZ2");

        verticalLayout->addWidget(lblCoordenadaZ2);

        spinZ2 = new QDoubleSpinBox(layoutWidget);
        spinZ2->setObjectName("spinZ2");

        verticalLayout->addWidget(spinZ2);

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

        lblCoordenadaZ3 = new QLabel(layoutWidget);
        lblCoordenadaZ3->setObjectName("lblCoordenadaZ3");

        verticalLayout->addWidget(lblCoordenadaZ3);

        spinZ3 = new QDoubleSpinBox(layoutWidget);
        spinZ3->setObjectName("spinZ3");

        verticalLayout->addWidget(spinZ3);

        lblRaio = new QLabel(layoutWidget);
        lblRaio->setObjectName("lblRaio");

        verticalLayout->addWidget(lblRaio);

        spinRaio = new QDoubleSpinBox(layoutWidget);
        spinRaio->setObjectName("spinRaio");
        spinRaio->setMaximum(100.000000000000000);

        verticalLayout->addWidget(spinRaio);

        lblTamanho = new QLabel(layoutWidget);
        lblTamanho->setObjectName("lblTamanho");

        verticalLayout->addWidget(lblTamanho);

        spinTamanho = new QDoubleSpinBox(layoutWidget);
        spinTamanho->setObjectName("spinTamanho");

        verticalLayout->addWidget(spinTamanho);

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


        retranslateUi(GerenciadorObjetosDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, GerenciadorObjetosDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, GerenciadorObjetosDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(GerenciadorObjetosDialog);
    } // setupUi

    void retranslateUi(QDialog *GerenciadorObjetosDialog)
    {
        GerenciadorObjetosDialog->setWindowTitle(QCoreApplication::translate("GerenciadorObjetosDialog", "Dialog", nullptr));
        lblForma->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Forma:", nullptr));
        lblCoordenadaX1->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coordenada X1:", nullptr));
        lblCoordenadaY1->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coodernada Y1:", nullptr));
        lblCoordenadaZ1->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coordenada Z1:", nullptr));
        lblCoordenadaX2->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coordenada X2:", nullptr));
        lblCoordenadaY2->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coodernada Y2:", nullptr));
        lblCoordenadaZ2->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coordenada Z2:", nullptr));
        lblCoordenadaX3->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coordenada X3:", nullptr));
        lblCoordenadaY3->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coordenada Y3:", nullptr));
        lblCoordenadaZ3->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coordenada Z3:", nullptr));
        lblRaio->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Raio:", nullptr));
        lblTamanho->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Tamanho", nullptr));
        btnCor->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Selecionar Cor", nullptr));
        btnDesenhar->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Adicionar", nullptr));
        btnModificarForma->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Modificar", nullptr));
        btnExcluirForma->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Excluir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GerenciadorObjetosDialog: public Ui_GerenciadorObjetosDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GERENCIADOROBJETOSDIALOG_H
