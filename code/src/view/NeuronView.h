#pragma once

#ifndef NEURONVIEW_H
#define NEURONVIEW_H

#include <QWidget>
#include "ui_NeuronView.h"
#include "../common/neurons.h"

QT_BEGIN_NAMESPACE
namespace Ui { class NeuronView; }
QT_END_NAMESPACE

class NeuronView : public QDialog {
    Q_OBJECT

signals:
    void sendData(QPair<QPair<int, double>, NeuronType>);

public:
    explicit NeuronView(QWidget* parent = nullptr);
    ~NeuronView();

    void setValue(double, NeuronType);
    void setID(int);
    QPair<int, double> getValue();
    NeuronType getType();
    QPair<QPair<int, double>, NeuronType> getData();

public slots:
    void saveData();
    void ignoreData();

private:
    QDoubleValidator *validator;
    Ui::NeuronView *ui;
    int neuron_id;
};

#endif
