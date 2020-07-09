/********************************************************************************
** Form generated from reading UI file 'visualized_neural_networks.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISUALIZED_NEURAL_NETWORKS_H
#define UI_VISUALIZED_NEURAL_NETWORKS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Visualized_Neural_NetworksClass
{
public:
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Visualized_Neural_NetworksClass)
    {
        if (Visualized_Neural_NetworksClass->objectName().isEmpty())
            Visualized_Neural_NetworksClass->setObjectName(QString::fromUtf8("Visualized_Neural_NetworksClass"));
        Visualized_Neural_NetworksClass->resize(600, 400);
        centralWidget = new QWidget(Visualized_Neural_NetworksClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Visualized_Neural_NetworksClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Visualized_Neural_NetworksClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Visualized_Neural_NetworksClass->setStatusBar(statusBar);

        retranslateUi(Visualized_Neural_NetworksClass);

        QMetaObject::connectSlotsByName(Visualized_Neural_NetworksClass);
    } // setupUi

    void retranslateUi(QMainWindow *Visualized_Neural_NetworksClass)
    {
        Visualized_Neural_NetworksClass->setWindowTitle(QCoreApplication::translate("Visualized_Neural_NetworksClass", "Visualized_Neural_Networks", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Visualized_Neural_NetworksClass: public Ui_Visualized_Neural_NetworksClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISUALIZED_NEURAL_NETWORKS_H
