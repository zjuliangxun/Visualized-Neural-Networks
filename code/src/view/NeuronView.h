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

signals:
    void sendData(QPair<int, double>);

public:
    explicit NeuronView(QWidget* parent = nullptr);
    ~NeuronView();

    void setValue(double);
    void setID(int);
    QPair<int, double> getValue();

public slots:
    void saveData();
    void ignoreData();

private:
    QDoubleValidator *validator;
    Ui::NeuronView *ui;
    int neuron_id;
};

#endif
