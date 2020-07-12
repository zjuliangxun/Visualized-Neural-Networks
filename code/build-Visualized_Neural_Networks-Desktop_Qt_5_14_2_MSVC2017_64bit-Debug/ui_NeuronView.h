/********************************************************************************
** Form generated from reading UI file 'NeuronView.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEURONVIEW_H
#define UI_NEURONVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_NeuronView
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *NeuronView)
    {
        if (NeuronView->objectName().isEmpty())
            NeuronView->setObjectName(QString::fromUtf8("NeuronView"));
        NeuronView->setWindowModality(Qt::NonModal);
        NeuronView->resize(430, 299);
        NeuronView->setModal(true);
        buttonBox = new QDialogButtonBox(NeuronView);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(NeuronView);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(210, 100, 113, 21));
        label = new QLabel(NeuronView);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 100, 141, 31));

        retranslateUi(NeuronView);
        QObject::connect(buttonBox, SIGNAL(accepted()), NeuronView, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NeuronView, SLOT(reject()));

        QMetaObject::connectSlotsByName(NeuronView);
    } // setupUi

    void retranslateUi(QDialog *NeuronView)
    {
        NeuronView->setWindowTitle(QCoreApplication::translate("NeuronView", "\347\245\236\347\273\217\345\205\203\347\274\226\350\276\221", nullptr));
#if QT_CONFIG(whatsthis)
        lineEdit->setWhatsThis(QCoreApplication::translate("NeuronView", "<html><head/><body><p>Enter a real number as the value of this input neuron.</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label->setText(QCoreApplication::translate("NeuronView", "\350\276\223\345\205\245\345\200\274(\346\265\256\347\202\271\346\225\260):\n"
"(-99.99,99.99)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NeuronView: public Ui_NeuronView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEURONVIEW_H
