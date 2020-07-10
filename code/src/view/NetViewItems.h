#pragma once

#ifndef NETVIEWITEMS_H
#define NETVIEWITEMS_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include "../common/neurons.h"
#include "../common/weights.h"

class NeuronItem : public QGraphicsEllipseItem {

public:
    // initialization
    NeuronItem(QGraphicsItem *parent = nullptr);
    NeuronItem(Neuron, QPointF, QGraphicsItem *parent = nullptr);
    ~NeuronItem();

    // bounding of nNone NeuronItem
    QRectF boundingRect() const override;

    // shape
    QPainterPath shape() const override;

    // painting of NeuronNone
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void setCenter(const QPointF);
    void setValue(const double);
    void setRadius(const int);

private:
    NeuronType _neuron_type;
    QPointF _center;
    double _value;
    static int _radius;
};

#endif
