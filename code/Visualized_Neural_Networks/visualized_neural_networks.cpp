#include "visualized_neural_networks.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QToolBar>

Visualized_Neural_Networks::Visualized_Neural_Networks(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    resize(800, 600);
    setWindowTitle("Visualized Neural Networks");

    _drag = noDrag;
    _selected_neuron = -1;
    _mode = selectNeuron;
    setMouseTracking(true);
    ui.centralWidget->setMouseTracking(true);

    QToolBar* tbar = addToolBar(tr("select"));
    tbar->setMovable(false);
    tbar->setIconSize(QSize(24, 24));
    tbar->setStyleSheet("background-color:rgb(255,255,255)");

    QAction* selectAction = new QAction(tr("&select"), this);
    selectAction->setIcon(QIcon("images/select.png"));
    tbar->addAction(selectAction);

    QAction* addNeuronNoneAction = new QAction(tr("&Neuron"), this);
    addNeuronNoneAction->setIcon(QIcon("images/neuron_none.png"));
    tbar->addAction(addNeuronNoneAction);

    QAction* addNeuronSigmoidAction = new QAction(tr("&Sigmoid"), this);
    addNeuronSigmoidAction->setIcon(QIcon("images/neuron_sigmoid.png"));
    tbar->addAction(addNeuronSigmoidAction);

    QAction* addNeuronReluAction = new QAction(tr("&Relu"), this);
    addNeuronReluAction->setIcon(QIcon("images/neuron_relu.png"));
    tbar->addAction(addNeuronReluAction);

    QAction* addNeuronTanhAction = new QAction(tr("&Tanh"), this);
    addNeuronTanhAction->setIcon(QIcon("images/neuron_tanh.png"));
    tbar->addAction(addNeuronTanhAction);

    QAction* addNeuronTargetAction = new QAction(tr("&Target"), this);
    addNeuronTargetAction->setIcon(QIcon("images/neuron_Target.png"));
    tbar->addAction(addNeuronTargetAction);


    // signal-slots connection
    connect(selectAction, SIGNAL(triggered()), this, SLOT(Select()));
    connect(addNeuronNoneAction, SIGNAL(triggered()), this, SLOT(AddNeuronNone()));
    connect(addNeuronSigmoidAction, SIGNAL(triggered()), this, SLOT(AddNeuronSigmoid()));
    connect(addNeuronReluAction, SIGNAL(triggered()), this, SLOT(AddNeuronRelu()));
    connect(addNeuronTanhAction, SIGNAL(triggered()), this, SLOT(AddNeuronTanh()));
    connect(addNeuronTargetAction, SIGNAL(triggered()), this, SLOT(AddNeuronTarget()));

}

int Visualized_Neural_Networks::_radius = 16;
QRect newQRect(QPoint, int);

void Visualized_Neural_Networks::paintEvent(QPaintEvent*)
{
    QPixmap map(size());
    map.fill(Qt::white);
    QPainter painter(&map);
    
    for (int i = 0; i != _neurons.size(); ++i) {
        switch (_neurons.at(i).type)
        {
        case nSigmoid:
            if (_mode == 1) {
                painter.setPen(QPen(Qt::darkRed, 1));
                painter.drawEllipse(_virtual_neuron._shape);
            }
            painter.setPen(QPen(Qt::darkRed, 2));
            break;
        case nRelu:
            if (_mode == 1) {
                painter.setPen(QPen(Qt::darkGreen, 1));
                painter.drawEllipse(_virtual_neuron._shape);
            }
            painter.setPen(QPen(Qt::darkGreen, 2));
            break;
        case nTanh:
            if (_mode == 1) {
                painter.setPen(QPen(Qt::darkBlue, 1));
                painter.drawEllipse(_virtual_neuron._shape);
            }
            painter.setPen(QPen(Qt::darkBlue, 2));
            break;
        case nTarget:
            if (_mode == 1) {
                painter.setPen(QPen(Qt::black, 1));
                painter.drawEllipse(_virtual_neuron._shape);
            }
            painter.setPen(QPen(Qt::black, 2));
            break;
        default:
            if (_mode == 1) {
                painter.setPen(QPen(Qt::black, 1));
                painter.drawEllipse(_virtual_neuron._shape);
            }
            painter.setPen(QPen(Qt::black, 2));
            break;
        }
        painter.drawEllipse(_neurons.at(i)._shape);
        if (_neurons.at(i).type == nTarget) {
            QRect outer = _neurons.at(i)._shape;
            outer.setTopLeft(QPoint(outer.left() - 3, outer.top() - 3));
            outer.setBottomRight(QPoint(outer.right() + 3, outer.bottom() + 3));
            painter.drawEllipse(outer);
        }
        if (_neuron_selected.at(i)) {
            QRect outer = _neurons.at(i)._shape;
            outer.setTopLeft(QPoint(outer.left() - 4, outer.top() - 4));
            outer.setBottomRight(QPoint(outer.right() + 4, outer.bottom() + 4));
            painter.drawRect(outer);
        }
    }
    
    painter.end();
    painter.begin(this);
    painter.drawPixmap(0, 0, map);
}

void Visualized_Neural_Networks::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        if (_mode == selectNeuron) {
            bool select_one = false;
            for (int i = 0; i != _neurons.size(); ++i) {
                QPoint old_c = _neurons.at(i)._shape.center();
                QPoint new_c(e->pos());
                int dx = old_c.x() - new_c.x();
                int dy = old_c.y() - new_c.y();
                if (dx * dx + dy * dy <= _radius * _radius) {
                    _neuron_selected.replace(i, true);
                    if (_selected_neuron == i)
                        _drag = canDrag;
                    else
                        _selected_neuron = i;
                    select_one = true;
                }
                else
                    _neuron_selected.replace(i, false);
            }
            if (select_one) {

            }
            else {
                _drag = noDrag;
                _selected_neuron = -1;
            }
        }
    }

    update();
}
void Visualized_Neural_Networks::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        if (_mode == selectNeuron) {
            for (int i = 0; i != _neurons.size(); ++i) {
                if (_neuron_selected.at(i) && i == _selected_neuron)
                    _drag = preDrag;
            }
        }
        else if (_mode == addNeuron) {
            Neuron x;
            x.isleaf = 1;
            x.type = _virtual_neuron.type;
            x._value = 0.0;
            int flag = true;
            for (int i = 0; i != _neurons.size() && flag; ++i) {
                QPoint old_c = _neurons.at(i)._shape.center();
                QPoint new_c(e->pos());
                int dx = old_c.x() - new_c.x();
                int dy = old_c.y() - new_c.y();
                if (dx * dx + dy * dy <= 4 * _radius * _radius)
                    flag = false;
            }
            if (flag) {
                x._shape = newQRect(e->pos(), _radius);
            }
            _neurons.append(x);
            _neuron_selected.append(false);
        }     
    }
    update();
}

void Visualized_Neural_Networks::mouseMoveEvent(QMouseEvent* e)
{
    _virtual_neuron._shape = newQRect(e->pos(), _radius);

    if (_drag == canDrag) {
        Neuron current_neuron(_neurons.at(_selected_neuron));
        current_neuron._shape.moveCenter(e->pos());
        int no_conflict = true;
        for (int i = 0; i != _neurons.size() && no_conflict; ++i) {
            if (i != _selected_neuron && 
                current_neuron.conflict(_neurons.at(i)))
                no_conflict = false;
        }
        if (no_conflict)
            _neurons.replace(_selected_neuron, current_neuron);
    }

    update();
}

void Visualized_Neural_Networks::Select()
{
    _virtual_neuron.type = nNone;
    _mode = selectNeuron;
    update();
}
void Visualized_Neural_Networks::AddNeuronNone()
{
    _virtual_neuron.type = nNone;
    _mode = addNeuron;
    update();
}
void Visualized_Neural_Networks::AddNeuronSigmoid()
{
    _virtual_neuron.type = nSigmoid;
    _mode = addNeuron;
    update();
}
void Visualized_Neural_Networks::AddNeuronRelu()
{
    _virtual_neuron.type = nRelu;
    _mode = addNeuron;
    update();
}
void Visualized_Neural_Networks::AddNeuronTanh()
{
    _virtual_neuron.type = nTanh;
    update();
    _mode = addNeuron;
}
void Visualized_Neural_Networks::AddNeuronTarget()
{
    _virtual_neuron.type = nTarget;
    _mode = addNeuron;
    update();
}

QRect newQRect(QPoint center, int radius)
{
    QPoint upper_left(center), lower_right(center);
    upper_left.setX(upper_left.x() - radius);
    upper_left.setY(upper_left.y() - radius);
    lower_right.setX(lower_right.x() + radius);
    lower_right.setY(lower_right.y() + radius);
    return QRect(upper_left, lower_right);
}