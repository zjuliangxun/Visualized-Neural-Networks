#include <QPainter>
#include "NetViewItems.h"
#include "utils.h"

int NeuronItem::_radius = 16;

NeuronItem::NeuronItem(QGraphicsItem *parent): QGraphicsEllipseItem(parent) {
    _neuron_type = nNone;
    _center = QPointF(0, 0);
}

NeuronItem::NeuronItem(Neuron neuron, QPointF pos, QGraphicsItem *parent)
    :QGraphicsEllipseItem(parent)
{
    _neuron_type = neuron.type;
    _center = pos;
}

NeuronItem::~NeuronItem()
{

}

QRectF NeuronItem::boundingRect() const
{
    int radius = _radius + 2;
    if (_neuron_type == nTarget)
        radius += 2;
    QPointF p1(_center.x() - radius,
               _center.y() - radius);
    QPointF p2(_center.x() + radius,
               _center.y() + radius);
    return QRectF(p1, p2);
}


// shape
QPainterPath NeuronItem::shape() const
{
    QRectF rect = newQRectF(_center, _radius + 2);
    if (_neuron_type == nTarget)
        rect = newQRectF(_center, _radius + 4);
    QPainterPath qpath;
    qpath.addEllipse(rect);
    return qpath;
}

// actual painting of NeuronNone
void NeuronItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor color = Qt::black;

    switch (_neuron_type) {
    case nNone:
        break;
    case nSigmoid:
        color = Qt::darkRed;
        break;
    case nRelu:
        color = Qt::darkBlue;
        break;
    case nTanh:
        color = Qt::darkGreen;
        break;
    case nTarget:
        break;
    default:
        break;
    }
    QPen pen(color);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->setBrush(color);
    painter->drawEllipse(newQRectF(_center, _radius));
    if (_neuron_type == nTarget)
        painter->drawEllipse(newQRectF(_center, _radius + 2));
}


void NeuronItem::setCenter(const QPointF p)
{
    _center = p;
}
void NeuronItem::setValue(const double x)
{
    _value = x;
}
void NeuronItem::setRadius(const int r)
{
    _radius = r;
}
