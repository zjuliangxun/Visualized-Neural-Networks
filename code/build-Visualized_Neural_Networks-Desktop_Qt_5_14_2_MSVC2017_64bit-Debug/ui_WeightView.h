/********************************************************************************
** Form generated from reading UI file 'WeightView.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEIGHTVIEW_H
#define UI_WEIGHTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_WeightView
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QDialog *WeightView)
    {
        if (WeightView->objectName().isEmpty())
            WeightView->setObjectName(QString::fromUtf8("WeightView"));
        WeightView->resize(400, 300);
        WeightView->setModal(true);
        buttonBox = new QDialogButtonBox(WeightView);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(WeightView);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 120, 131, 31));
        lineEdit = new QLineEdit(WeightView);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(170, 120, 113, 21));

        retranslateUi(WeightView);
        QObject::connect(buttonBox, SIGNAL(accepted()), WeightView, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), WeightView, SLOT(reject()));

        QMetaObject::connectSlotsByName(WeightView);
    } // setupUi

    void retranslateUi(QDialog *WeightView)
    {
        WeightView->setWindowTitle(QCoreApplication::translate("WeightView", "\346\235\203\351\207\215\347\274\226\350\276\221", nullptr));
        label->setText(QCoreApplication::translate("WeightView", "\350\276\223\345\205\245\346\235\203\345\200\274(\346\265\256\347\202\271\346\225\260):\n"
"(-99.99,99.99)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WeightView: public Ui_WeightView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEIGHTVIEW_H
