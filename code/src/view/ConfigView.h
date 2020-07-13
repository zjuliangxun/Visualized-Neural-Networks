#pragma once

#ifndef CONFIGVIEW_H
#define CONFIGVIEW_H


#include <QWidget>
#include "ui_ConfigView.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ConfigView; }
QT_END_NAMESPACE

class ConfigView : public QDialog {
    Q_OBJECT

signals:
    void sendData(QPair<double, QString>);

public:
    explicit ConfigView(QWidget* parent = nullptr);
    ~ConfigView();

    void setValue(double, QString);
    QPair<double, QString> getValue();

public slots:
    void saveData();
    void ignoreData();

private:
    QDoubleValidator *validator;
    Ui::ConfigView *ui;
    int Config_id;
};

#endif // CONFIGVIEW_H
