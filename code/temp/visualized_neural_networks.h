#pragma once

#ifndef VISUALIZED_NEURAL_NETWORKS_H
#define VISUALIZED_NEURAL_NETWORKS_H

#include <QSharedPointer>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include "ui_visualized_neural_networks.h"
#include "neurons.h"

enum EditMode {
    selectNeuron, addNeuron, addWeight
};
enum DragMode {
    noDrag, preDrag, canDrag
};

class Visualized_Neural_Networks : public QMainWindow
{
    Q_OBJECT

public:
    Visualized_Neural_Networks(QWidget *parent = Q_NULLPTR);

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    /*void contextMenuEvent(QContextMenuEvent*);
    void keyPressEvent(QKeyEvent*);*/

private:
    DragMode _drag;
    int _selected_neuron;
    QPixmap _pixmap;
    EditMode _mode;             // {select, place}
    static int _radius;         // neuron radius
    QVector<bool> _neuron_selected;    // whether neuron is selected

public:
    QVector<Neuron> _neurons;   // neurons
    Neuron _virtual_neuron;     // current place

private:
    Ui::Visualized_Neural_NetworksClass ui;

signals:

public slots:
    void AddNeuronNone();
    void AddNeuronSigmoid();
    void AddNeuronRelu();
    void AddNeuronTanh();
    void AddNeuronTarget();
    void Select();
};

#endif // !VISUALIZED_NEURAL_NETWORKS_H