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
public:
    explicit WeightView(QWidget* parent = nullptr);
    ~WeightView();

    void setWeight(double);
    double getWeight();

private:
    QDoubleValidator *validator;
    Ui::WeightView *ui;
};

#endif
