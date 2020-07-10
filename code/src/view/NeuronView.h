#pragma once

#ifndef NEURONVIEW_H
#define NEURONVIEW_H

#include <QWidget>
#include "ui_NeuronView.h"

QT_BEGIN_NAMESPACE
namespace Ui { class NeuronView; }
QT_END_NAMESPACE

class NeuronView : public QDialog {
    Q_OBJECT
public:
    explicit NeuronView(QWidget* parent = nullptr);
    ~NeuronView();

    void setValue(double);
    double getValue();

private:
    QDoubleValidator *validator;
    Ui::NeuronView *ui;
};

#endif
