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
#include <QtWidgets/QHBoxLayout>
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
    QHBoxLayout *horizontalLayout;
    QPushButton *btnExcluirForma;
    QPushButton *btnModificarForma;
    QPushButton *btnDesenhar;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblForma;
    QComboBox *comboFormas;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_5;
    QLabel *lblCoordenadaX1;
    QDoubleSpinBox *spinX1;
    QLabel *lblCoordenadaX2;
    QDoubleSpinBox *spinX2;
    QLabel *lblCoordenadaX3;
    QDoubleSpinBox *spinX3;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_6;
    QLabel *lblCoordenadaY1;
    QDoubleSpinBox *spinY1;
    QLabel *lblCoordenadaY2;
    QDoubleSpinBox *spinY2;
    QLabel *lblCoordenadaY3;
    QDoubleSpinBox *spinY3;
    QWidget *widget3;
    QVBoxLayout *verticalLayout_7;
    QLabel *lblCoordenadaZ1;
    QDoubleSpinBox *spinZ1;
    QLabel *lblCoordenadaZ2;
    QDoubleSpinBox *spinZ2;
    QLabel *lblCoordenadaZ3;
    QDoubleSpinBox *spinZ3;
    QWidget *widget4;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *lblRaio;
    QDoubleSpinBox *spinRaio;
    QVBoxLayout *verticalLayout_3;
    QLabel *lblTamanho;
    QDoubleSpinBox *spinTamanho;
    QPushButton *btnCor;

    void setupUi(QDialog *GerenciadorObjetosDialog)
    {
        if (GerenciadorObjetosDialog->objectName().isEmpty())
            GerenciadorObjetosDialog->setObjectName("GerenciadorObjetosDialog");
        GerenciadorObjetosDialog->setWindowModality(Qt::WindowModality::NonModal);
        GerenciadorObjetosDialog->resize(581, 394);
        buttonBox = new QDialogButtonBox(GerenciadorObjetosDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(380, 340, 181, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        layoutWidget = new QWidget(GerenciadorObjetosDialog);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(300, 300, 258, 29));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnExcluirForma = new QPushButton(layoutWidget);
        btnExcluirForma->setObjectName("btnExcluirForma");

        horizontalLayout->addWidget(btnExcluirForma);

        btnModificarForma = new QPushButton(layoutWidget);
        btnModificarForma->setObjectName("btnModificarForma");

        horizontalLayout->addWidget(btnModificarForma);

        btnDesenhar = new QPushButton(layoutWidget);
        btnDesenhar->setObjectName("btnDesenhar");

        horizontalLayout->addWidget(btnDesenhar);

        widget = new QWidget(GerenciadorObjetosDialog);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 20, 531, 61));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lblForma = new QLabel(widget);
        lblForma->setObjectName("lblForma");

        verticalLayout_2->addWidget(lblForma);

        comboFormas = new QComboBox(widget);
        comboFormas->setObjectName("comboFormas");

        verticalLayout_2->addWidget(comboFormas);

        widget1 = new QWidget(GerenciadorObjetosDialog);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(20, 100, 117, 173));
        verticalLayout_5 = new QVBoxLayout(widget1);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        lblCoordenadaX1 = new QLabel(widget1);
        lblCoordenadaX1->setObjectName("lblCoordenadaX1");

        verticalLayout_5->addWidget(lblCoordenadaX1);

        spinX1 = new QDoubleSpinBox(widget1);
        spinX1->setObjectName("spinX1");
        spinX1->setMaximum(600.000000000000000);

        verticalLayout_5->addWidget(spinX1);

        lblCoordenadaX2 = new QLabel(widget1);
        lblCoordenadaX2->setObjectName("lblCoordenadaX2");

        verticalLayout_5->addWidget(lblCoordenadaX2);

        spinX2 = new QDoubleSpinBox(widget1);
        spinX2->setObjectName("spinX2");
        spinX2->setMaximum(600.000000000000000);

        verticalLayout_5->addWidget(spinX2);

        lblCoordenadaX3 = new QLabel(widget1);
        lblCoordenadaX3->setObjectName("lblCoordenadaX3");
        lblCoordenadaX3->setEnabled(true);

        verticalLayout_5->addWidget(lblCoordenadaX3);

        spinX3 = new QDoubleSpinBox(widget1);
        spinX3->setObjectName("spinX3");
        spinX3->setMaximum(600.000000000000000);

        verticalLayout_5->addWidget(spinX3);

        widget2 = new QWidget(GerenciadorObjetosDialog);
        widget2->setObjectName("widget2");
        widget2->setGeometry(QRect(160, 100, 118, 173));
        verticalLayout_6 = new QVBoxLayout(widget2);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        lblCoordenadaY1 = new QLabel(widget2);
        lblCoordenadaY1->setObjectName("lblCoordenadaY1");

        verticalLayout_6->addWidget(lblCoordenadaY1);

        spinY1 = new QDoubleSpinBox(widget2);
        spinY1->setObjectName("spinY1");
        spinY1->setMaximum(600.000000000000000);

        verticalLayout_6->addWidget(spinY1);

        lblCoordenadaY2 = new QLabel(widget2);
        lblCoordenadaY2->setObjectName("lblCoordenadaY2");

        verticalLayout_6->addWidget(lblCoordenadaY2);

        spinY2 = new QDoubleSpinBox(widget2);
        spinY2->setObjectName("spinY2");
        spinY2->setMaximum(600.000000000000000);

        verticalLayout_6->addWidget(spinY2);

        lblCoordenadaY3 = new QLabel(widget2);
        lblCoordenadaY3->setObjectName("lblCoordenadaY3");
        lblCoordenadaY3->setEnabled(true);

        verticalLayout_6->addWidget(lblCoordenadaY3);

        spinY3 = new QDoubleSpinBox(widget2);
        spinY3->setObjectName("spinY3");
        spinY3->setMaximum(600.000000000000000);

        verticalLayout_6->addWidget(spinY3);

        widget3 = new QWidget(GerenciadorObjetosDialog);
        widget3->setObjectName("widget3");
        widget3->setGeometry(QRect(300, 100, 117, 173));
        verticalLayout_7 = new QVBoxLayout(widget3);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        lblCoordenadaZ1 = new QLabel(widget3);
        lblCoordenadaZ1->setObjectName("lblCoordenadaZ1");

        verticalLayout_7->addWidget(lblCoordenadaZ1);

        spinZ1 = new QDoubleSpinBox(widget3);
        spinZ1->setObjectName("spinZ1");

        verticalLayout_7->addWidget(spinZ1);

        lblCoordenadaZ2 = new QLabel(widget3);
        lblCoordenadaZ2->setObjectName("lblCoordenadaZ2");

        verticalLayout_7->addWidget(lblCoordenadaZ2);

        spinZ2 = new QDoubleSpinBox(widget3);
        spinZ2->setObjectName("spinZ2");

        verticalLayout_7->addWidget(spinZ2);

        lblCoordenadaZ3 = new QLabel(widget3);
        lblCoordenadaZ3->setObjectName("lblCoordenadaZ3");

        verticalLayout_7->addWidget(lblCoordenadaZ3);

        spinZ3 = new QDoubleSpinBox(widget3);
        spinZ3->setObjectName("spinZ3");

        verticalLayout_7->addWidget(spinZ3);

        widget4 = new QWidget(GerenciadorObjetosDialog);
        widget4->setObjectName("widget4");
        widget4->setGeometry(QRect(430, 100, 123, 171));
        verticalLayout = new QVBoxLayout(widget4);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        lblRaio = new QLabel(widget4);
        lblRaio->setObjectName("lblRaio");

        verticalLayout_4->addWidget(lblRaio);

        spinRaio = new QDoubleSpinBox(widget4);
        spinRaio->setObjectName("spinRaio");
        spinRaio->setMaximum(100.000000000000000);

        verticalLayout_4->addWidget(spinRaio);


        verticalLayout->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        lblTamanho = new QLabel(widget4);
        lblTamanho->setObjectName("lblTamanho");

        verticalLayout_3->addWidget(lblTamanho);

        spinTamanho = new QDoubleSpinBox(widget4);
        spinTamanho->setObjectName("spinTamanho");

        verticalLayout_3->addWidget(spinTamanho);

        btnCor = new QPushButton(widget4);
        btnCor->setObjectName("btnCor");

        verticalLayout_3->addWidget(btnCor);


        verticalLayout->addLayout(verticalLayout_3);


        retranslateUi(GerenciadorObjetosDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, GerenciadorObjetosDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, GerenciadorObjetosDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(GerenciadorObjetosDialog);
    } // setupUi

    void retranslateUi(QDialog *GerenciadorObjetosDialog)
    {
        GerenciadorObjetosDialog->setWindowTitle(QCoreApplication::translate("GerenciadorObjetosDialog", "Gerador de Formas", nullptr));
        btnExcluirForma->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Excluir", nullptr));
        btnModificarForma->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Modificar", nullptr));
        btnDesenhar->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Adicionar", nullptr));
        lblForma->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Forma:", nullptr));
        lblCoordenadaX1->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coordenada X1:", nullptr));
        lblCoordenadaX2->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coordenada X2:", nullptr));
        lblCoordenadaX3->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coordenada X3:", nullptr));
        lblCoordenadaY1->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coodernada Y1:", nullptr));
        lblCoordenadaY2->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coodernada Y2:", nullptr));
        lblCoordenadaY3->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coordenada Y3:", nullptr));
        lblCoordenadaZ1->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coordenada Z1:", nullptr));
        lblCoordenadaZ2->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coordenada Z2:", nullptr));
        lblCoordenadaZ3->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Coordenada Z3:", nullptr));
        lblRaio->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Raio:", nullptr));
        lblTamanho->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Tamanho", nullptr));
        btnCor->setText(QCoreApplication::translate("GerenciadorObjetosDialog", "Selecionar Cor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GerenciadorObjetosDialog: public Ui_GerenciadorObjetosDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GERENCIADOROBJETOSDIALOG_H
