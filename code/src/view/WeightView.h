#pragma once

#ifndef WEIGHTVIEW_H
#define WEIGHTVIEW_H

#include <QWidget>
#include "ui_WeightView.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WeightView; }
QT_END_NAMESPACE

class WeightView : public QDialog {
    Q_OBJECT

signals:
    void sendData(QPair<int, double>);

public:
    explicit WeightView(QWidget* parent = nullptr);
    ~WeightView();

    void setWeight(double);
    void setID(int);
    QPair<int, double> getWeight();

public slots:
    void saveData();
    void ignoreData();

private:
    QDoubleValidator *validator;
    Ui::WeightView *ui;
    int weight_id;
};


#endif
