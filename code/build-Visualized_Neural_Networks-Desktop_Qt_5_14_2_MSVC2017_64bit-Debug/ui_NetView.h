/********************************************************************************
** Form generated from reading UI file 'NetView.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETVIEW_H
#define UI_NETVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetView
{
public:
    QAction *actionForward;
    QAction *actionManual;
    QAction *actionAbout;
    QAction *actionGradient_calculate;
    QAction *actionGradient_propagate;
    QAction *actionUpdate_weights;
    QAction *actionRun_all;
    QAction *actionDelete;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menuBackpropagation;
    QMenu *menu_4;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NetView)
    {
        if (NetView->objectName().isEmpty())
            NetView->setObjectName(QString::fromUtf8("NetView"));
        NetView->resize(800, 600);
        actionForward = new QAction(NetView);
        actionForward->setObjectName(QString::fromUtf8("actionForward"));
        actionManual = new QAction(NetView);
        actionManual->setObjectName(QString::fromUtf8("actionManual"));
        actionAbout = new QAction(NetView);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionGradient_calculate = new QAction(NetView);
        actionGradient_calculate->setObjectName(QString::fromUtf8("actionGradient_calculate"));
        actionGradient_propagate = new QAction(NetView);
        actionGradient_propagate->setObjectName(QString::fromUtf8("actionGradient_propagate"));
        actionUpdate_weights = new QAction(NetView);
        actionUpdate_weights->setObjectName(QString::fromUtf8("actionUpdate_weights"));
        actionRun_all = new QAction(NetView);
        actionRun_all->setObjectName(QString::fromUtf8("actionRun_all"));
        actionDelete = new QAction(NetView);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        centralwidget = new QWidget(NetView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        NetView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(NetView);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menuBackpropagation = new QMenu(menu_3);
        menuBackpropagation->setObjectName(QString::fromUtf8("menuBackpropagation"));
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        NetView->setMenuBar(menubar);
        statusbar = new QStatusBar(NetView);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        NetView->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menu_2->addAction(actionDelete);
        menu_3->addAction(actionForward);
        menu_3->addAction(menuBackpropagation->menuAction());
        menuBackpropagation->addAction(actionRun_all);
        menuBackpropagation->addSeparator();
        menuBackpropagation->addAction(actionGradient_calculate);
        menuBackpropagation->addAction(actionGradient_propagate);
        menuBackpropagation->addAction(actionUpdate_weights);

        retranslateUi(NetView);

        QMetaObject::connectSlotsByName(NetView);
    } // setupUi

    void retranslateUi(QMainWindow *NetView)
    {
        NetView->setWindowTitle(QCoreApplication::translate("NetView", "NetView", nullptr));
        actionForward->setText(QCoreApplication::translate("NetView", "Forward", nullptr));
        actionManual->setText(QCoreApplication::translate("NetView", "Manual", nullptr));
        actionAbout->setText(QCoreApplication::translate("NetView", "About", nullptr));
        actionGradient_calculate->setText(QCoreApplication::translate("NetView", "Gradient Calculate", nullptr));
        actionGradient_propagate->setText(QCoreApplication::translate("NetView", "Gradient Propagate", nullptr));
        actionUpdate_weights->setText(QCoreApplication::translate("NetView", "Update Weights", nullptr));
        actionRun_all->setText(QCoreApplication::translate("NetView", "Run All", nullptr));
        actionDelete->setText(QCoreApplication::translate("NetView", "Delete", nullptr));
        menu->setTitle(QCoreApplication::translate("NetView", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("NetView", "\347\274\226\350\276\221", nullptr));
        menu_3->setTitle(QCoreApplication::translate("NetView", "\350\256\241\347\256\227", nullptr));
        menuBackpropagation->setTitle(QCoreApplication::translate("NetView", "Backpropagation", nullptr));
        menu_4->setTitle(QCoreApplication::translate("NetView", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NetView: public Ui_NetView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETVIEW_H
