#include <QPair>
#include <QToolBar>
#include <QPainter>
#include <QMouseEvent>
#include <cmath>

#include "NetView.h"
#include "ui_NetView.h"
#include "utils.h"

/* auxiliary functions */
static int _radius = 24;

/* View Definition */
NetView::NetView(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::NetView)
{
    /* display basic UI */
    ui->setupUi(this);
    resize(800, 600);
    setWindowTitle("Visualized Neural Networks");

    setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);

    /* display tool bar */
    QToolBar* tbar = addToolBar(tr("Tool Bar"));
    tbar->setMovable(false);
    tbar->setIconSize(QSize(24, 24));
    tbar->setStyleSheet("background-color:rgb(255,255,255)");

    QAction* selectAction = new QAction(tr("&select"), this);
    selectAction->setIcon(QIcon(":/images/select.png"));
    tbar->addAction(selectAction);

    QAction* addNeuronNoneAction = new QAction(tr("&Neuron"), this);
    addNeuronNoneAction->setIcon(QIcon(":/images/neuron_none.png"));
    tbar->addAction(addNeuronNoneAction);

    QAction* addNeuronSigmoidAction = new QAction(tr("&Sigmoid"), this);
    addNeuronSigmoidAction->setIcon(QIcon(":/images/neuron_sigmoid.png"));
    tbar->addAction(addNeuronSigmoidAction);

    QAction* addNeuronReluAction = new QAction(tr("&Relu"), this);
    addNeuronReluAction->setIcon(QIcon(":/images/neuron_relu.png"));
    tbar->addAction(addNeuronReluAction);

    QAction* addNeuronTanhAction = new QAction(tr("&Tanh"), this);
    addNeuronTanhAction->setIcon(QIcon(":/images/neuron_tanh.png"));
    tbar->addAction(addNeuronTanhAction);

    QAction* addNeuronTargetAction = new QAction(tr("&Target"), this);
    addNeuronTargetAction->setIcon(QIcon(":/images/neuron_target.png"));
    tbar->addAction(addNeuronTargetAction);

    // signal-slots connection
    connect(selectAction, SIGNAL(triggered()), this, SLOT(select_button_clicked()));
    connect(addNeuronNoneAction, SIGNAL(triggered()), this, SLOT(neuron_button_clicked()));
    connect(addNeuronSigmoidAction, SIGNAL(triggered()), this, SLOT(sigmoid_button_clicked()));
    connect(addNeuronReluAction, SIGNAL(triggered()), this, SLOT(relu_button_clicked()));
    connect(addNeuronTanhAction, SIGNAL(triggered()), this, SLOT(tanh_button_clicked()));
    connect(addNeuronTargetAction, SIGNAL(triggered()), this, SLOT(target_button_clicked()));

    connect(ui->actionForward, SIGNAL(triggered()), this, SLOT(calc_forward_clicked()));
    connect(ui->actionGradient_calculate, SIGNAL(triggered()), this, SLOT(calc_gradient_clicked()));
    connect(ui->actionGradient_propagate, SIGNAL(triggered()), this, SLOT(prop_gradient_clicked()));
    connect(ui->actionUpdate_weights, SIGNAL(triggered()), this, SLOT(update_weights_clicked()));
    connect(ui->actionRun_all, SIGNAL(triggered()), this, SLOT(backprop_clicked()));
    connect(ui->actionDelete, SIGNAL(triggered()), this, SLOT(delete_button_clicked()));
    connect(ui->actionConfigure, SIGNAL(triggered()), this, SLOT(enter_config()));

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exit_clicked()));
    connect(ui->actionPlain_Neuron, SIGNAL(triggered()), this, SLOT(neuron_button_clicked()));
    connect(ui->actionSigmoid_Neuron, SIGNAL(triggered()), this, SLOT(sigmoid_button_clicked()));
    connect(ui->actionRelu_Neuron, SIGNAL(triggered()), this, SLOT(relu_button_clicked()));
    connect(ui->actionTanh_Neuron, SIGNAL(triggered()), this, SLOT(tanh_button_clicked()));
    connect(ui->actionTarget, SIGNAL(triggered()), this, SLOT(target_button_clicked()));
    connect(ui->actionIterate, SIGNAL(triggered()), this, SLOT(iterate_clicked()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about_clicked()));
    connect(ui->actionTutorial, SIGNAL(triggered()), this, SLOT(tutorial_clicked()));

    // initialize internal states
    selected_neuron = -1;
    selected_weight = -1;
    edit_mode = selectNeuron;
    drag_mode = noDrag;
    neuronView = nullptr;
    weightView = nullptr;
    configView = nullptr;
}

NetView::~NetView()
{
    delete ui;
}


void NetView::set_FNN(std::shared_ptr<Graph> pFNN)
{
    this->FNN = pFNN;
    for (int i = 0; i != pFNN->_neurons.size(); ++i) {
        neuron_ids.append(pFNN->_neurons.at(i).id);
    }
    for (int i = 0; i != pFNN->_weights.size(); ++i) {
        weight_ids.append(pFNN->_neurons.at(i).id);
    }
}


/* Define Events */
void NetView::paintEvent(QPaintEvent*)
{
    QPixmap map(size());
    map.fill(Qt::white);
    QPainter painter(&map);
    // paint neurons
    this->paintNeurons(&painter);
    // paint weights
    this->paintWeights(&painter);
    painter.end();
    painter.begin(this);
    painter.drawPixmap(0, 0, map);
}
void NetView::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        if (edit_mode == selectNeuron) {
            bool select_one = false;
            // select neuron
            for (int i = 0; i != this->FNN->_neurons.size(); ++i) {
                if (isinside(e->pos(), shape_neurons.at(i), _radius)) {
                    if (selected_neuron == this->FNN->_neurons.at(i).id)
                        drag_mode = canDrag;
                    else
                        selected_neuron = this->FNN->_neurons.at(i).id;
                    select_one = true;
                }
            }
            if (select_one)
                return;
            drag_mode = noDrag;
            selected_neuron = -1;
            // select weight
            for (int i = 0; i != this->FNN->_weights.size(); ++i) {
                if (nearline(e->pos(), shape_weights.at(i))) {
                    selected_weight = this->FNN->_weights.at(i).id;
                    select_one = true;
                }
            }
            if (!select_one)
                selected_weight = -1;
            update();
        }
    }
    else if (e->button() == Qt::RightButton) {
        if (edit_mode == selectNeuron) {
            if (selected_neuron != -1) {
                drag_mode = lineDrag;
                for (int i = 0; i != this->FNN->_neurons.size(); ++i) {
                    if (this->FNN->_neurons.at(i).id == selected_neuron)
                        shape_current_weight.setP1(e->pos());
                }
                shape_current_weight.setP2(e->pos());
            }
            selected_weight = -1;
            update();
        }
    }
}
void NetView::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        if (edit_mode == selectNeuron) {
            for (int i = 0; i != this->FNN->_neurons.size(); ++i) {
                if (this->FNN->_neurons.at(i).id == selected_neuron)
                    drag_mode = preDrag;
            }
            update();
        }
        else if (edit_mode == addNeuron) {
            Neuron x;
            QRectF shape_x;
            x.isleaf = nInput;
            x.type = current_neuron.type;
            x._value = 0.0;
            int flag = true;
            for (int i = 0; i != this->FNN->_neurons.size() && flag; ++i) {
                if (conflict(e->pos(), shape_neurons.at(i)))
                    flag = false;
            }
            if (flag) {
                shape_x = newQRectF(e->pos(), _radius);
            }

            bool add_success = add_neuron_command(x);  // with return falue
            if (add_success) {
                shape_neurons.append(shape_x);
            }
            update();
        }
    }
    else if (e->button() == Qt::RightButton) {
        if (edit_mode == selectNeuron && drag_mode == lineDrag) {
            for (int i = 0; i != this->FNN->_neurons.size(); ++i) {
                if (isinside(e->pos(), shape_neurons.at(i))) {
                    QPair<int, int> param(selected_neuron, this->FNN->_neurons.at(i).id);
                    bool connect_success = (param.first != param.second);
                    connect_success &= connect_command(param);
                    if (connect_success) {
                        topology_weights.append(param);
                    }
                    break;
                }
            }
            selected_neuron = -1;
            drag_mode = noDrag;
            shape_current_weight.setP1(e->pos());
            shape_current_weight.setP2(e->pos());
            update();
        }
    }
}
void NetView::mouseDoubleClickEvent(QMouseEvent* e)
{
    bool triggered = false;
    for (int i = 0; i != this->FNN->_neurons.size() && !triggered; ++i) {
        if (isinside(e->pos(), shape_neurons.at(i))) {
            neuronView = new NeuronView(this);
            connect(neuronView,
                    SIGNAL(sendData(QPair<QPair<int, double>, NeuronType>)),
                    this,
                    SLOT(change_neuron_value(QPair<QPair<int, double>, NeuronType>)));
            if (this->FNN->_neurons.at(i).type == nTarget)
                neuronView->setValue(
                            this->FNN->_neurons.at(i)._targetvalue,
                            this->FNN->_neurons.at(i).type);
            else
                neuronView->setValue(
                            this->FNN->_neurons.at(i)._value,
                            this->FNN->_neurons.at(i).type);
            neuronView->setID(this->FNN->_neurons.at(i).id);
            if (neuronView->exec() == QDialog::Accepted) {
                update();
            }
            else {
                /* error */
            }
            triggered = true;
        }
    }
    // weight
    for (int i = 0; i != this->FNN->_weights.size() && !triggered; ++i) {
        if (nearline(e->pos(), shape_weights.at(i), 5)) {
            weightView = new WeightView(this);
            connect(weightView,
                    SIGNAL(sendData(QPair<int, double>)),
                    this,
                    SLOT(change_weight_value(QPair<int, double>)));
            weightView->setWeight(this->FNN->_weights.at(i)._weight);
            weightView->setID(this->FNN->_weights.at(i).id);
            if (weightView->exec() == QDialog::Accepted) {
                update();
            }
            else {
                /* error */
            }
            triggered = true;
        }
    }
}
void NetView::mouseMoveEvent(QMouseEvent* e)
{
    shape_current_neuron = newQRectF(e->pos(), _radius);

    if (drag_mode == canDrag) {
//        drag_mode = isDrag;
        shape_current_neuron.moveCenter(e->pos());
        int no_conflict = true;
        for (int i = 0; i != shape_neurons.size() && no_conflict; ++i) {
            if (this->FNN->_neurons.at(i).id != selected_neuron &&
                conflict(shape_current_neuron, shape_neurons.at(i)))
                no_conflict = false;
        }
        if (no_conflict) {
            for (int i = 0; i != shape_neurons.size(); ++i) {
                if (this->FNN->_neurons.at(i).id == selected_neuron) {
                    shape_neurons.replace(i, shape_current_neuron);
                    break;
                }
            }
        }
    }
    else if (drag_mode == lineDrag) {
        shape_current_weight.setP2(e->pos());
    }
    update();
}


/* Binding Commands */
void NetView::set_add_neuron_command(Command&& cmd) {
    this->add_neuron_command = std::move(cmd);
}
void NetView::set_connect_command(Command&& cmd) {
    this->connect_command = std::move(cmd);
}
void NetView::set_change_neuron_command(Command &&cmd) {
    this->change_neuron_command = std::move(cmd);
}
void NetView::set_change_weight_command(Command &&cmd) {
    this->change_weight_command = std::move(cmd);
}
void NetView::set_calculate_forward_command(Command &&cmd) {
    this->calculate_forward_command = std::move(cmd);
}
void NetView::set_calculate_gradient_command(Command &&cmd) {
    this->calculate_gradient_command = std::move(cmd);
}
void NetView::set_propagate_gradient_command(Command &&cmd) {
    this->propagate_gradient_command = std::move(cmd);
}
void NetView::set_update_weights_command(Command &&cmd) {
    this->update_weights_command = std::move(cmd);
}
void NetView::set_backprop_command(Command &&cmd) {
    this->backprop_command = std::move(cmd);
}
void NetView::set_delete_weight_command(Command &&cmd) {
    this->delete_weight_command = std::move(cmd);
}
void NetView::set_delete_neuron_command(Command &&cmd) {
    this->delete_neuron_command = std::move(cmd);
}
void NetView::set_change_learning_rate_command(Command &&cmd) {
    this->change_learning_rate_command = std::move(cmd);
}
void NetView::set_change_loss_command(Command &&cmd) {
    this->change_loss_command = std::move(cmd);
}
void NetView::set_demand_config_command(Command &&cmd)
{
    this->demand_config_command = std::move(cmd);
}



/* Binding Notifications */
Notification NetView::tell_update_view_notification() {
    return [this](uint32_t uID) {
        if (uID == NOTIF_DRAW)
            update();
	};
}
Notification NetView::tell_property_change_notification() {
    return [this](uint32_t uID) {
        if (uID == NOTIF_CHANGE) {
            check_FNN();
//            update();
        }
    };
}

/* Toolbar Reaction */
void NetView::select_button_clicked()
{
    current_neuron.type = nNone;
    edit_mode = selectNeuron;
    update();
}
void NetView::neuron_button_clicked()
{
    current_neuron.type = nNone;
    edit_mode = addNeuron;
    selected_neuron = -1;
    selected_weight = -1;
    update();
}
void NetView::sigmoid_button_clicked()
{
    current_neuron.type = nSigmoid;
    edit_mode = addNeuron;
    selected_neuron = -1;
    selected_weight = -1;
    update();
}
void NetView::relu_button_clicked()
{
    current_neuron.type = nRelu;
    edit_mode = addNeuron;
    selected_neuron = -1;
    selected_weight = -1;
    update();
}
void NetView::tanh_button_clicked()
{
    current_neuron.type = nTanh;
    edit_mode = addNeuron;
    selected_neuron = -1;
    selected_weight = -1;
    update();
}
void NetView::target_button_clicked()
{
    current_neuron.type = nTarget;
    edit_mode = addNeuron;
    selected_neuron = -1;
    selected_weight = -1;
    update();
}
void NetView::change_neuron_value(QPair<QPair<int, double>, NeuronType> data)
{
    change_neuron_command(data);    // now no failure dealing
}
void NetView::change_weight_value(QPair<int, double> data)
{
    change_weight_command(data);
}
void NetView::change_learning_rate(double x)
{
    change_learning_rate_command(x);
}
void NetView::change_loss(QString s)
{
    change_loss_command(s);
}
void NetView::change_config(QPair<double, QString> config)
{
    change_learning_rate(config.first);
    change_loss(config.second);
}

/* Menu Reaction */
void NetView::calc_forward_clicked()
{
    int flag;
    bool calc_success = calculate_forward_command(&flag);
    if (calc_success) {
        update();
    }
    else {
        /* check */
    }
}
void NetView::calc_gradient_clicked()
{
    int flag;
    bool calc_success = calculate_gradient_command(&flag);
    if (calc_success) {
        update();
    }
    else {
        /* check */
    }
}
void NetView::prop_gradient_clicked()
{
    int flag;
    bool calc_success = propagate_gradient_command(&flag);
    if (calc_success) {
        update();
    }
    else {
        /* check */
    }
}
void NetView::update_weights_clicked()
{
    int flag;
    bool calc_success = update_weights_command(&flag);
    if (calc_success) {
        update();
    }
    else {
        /* check */
    }
}
void NetView::backprop_clicked()
{
    int flag;
    bool calc_success = backprop_command(&flag);
    if (calc_success) {
        update();
    }
    else {
        /* check */
    }
}
void NetView::delete_button_clicked()
{
    bool success = true;
    if (selected_neuron != -1) {
        success = delete_neuron_command(selected_neuron);
        selected_neuron = -1;
    }
    else if (selected_weight != -1) {
        success = delete_weight_command(selected_weight);
        selected_weight = -1;
    }
    if (success)
        update();
    else {
        /**/
    }
}
void NetView::enter_config()
{
    configView = new ConfigView;
    connect(configView,
            SIGNAL(sendData(QPair<double, QString>)),
            this,
            SLOT(change_config(QPair<double, QString>)));
    QPair<double, QString> current_config;
    demand_config_command(&current_config);
    configView->setValue(current_config.first, current_config.second);
    if (configView->exec() == QDialog::Accepted) {
        update();
    }
    else {
        /* error */
    }
}
void NetView::exit_clicked()
{
    this->close();
}
void NetView::iterate_clicked()
{
    calc_forward_clicked();
    calc_gradient_clicked();
    prop_gradient_clicked();
    update_weights_clicked();
}
void NetView::about_clicked()
{
    aboutView = new About;
    aboutView->show();
}
void NetView::tutorial_clicked()
{
    tutorialView = new Tutorial;
    tutorialView->show();
}

/* Internal Functions */
void NetView::check_FNN_neurons()
{
    // check neurons (model delete)
    auto iter1 = shape_neurons.begin();
    auto iter2 = neuron_ids.begin();
    while (iter1 != shape_neurons.end()) {
        int id = *iter2;
        bool found = false;
        for (auto p = this->FNN->_neurons.begin();
             p != this->FNN->_neurons.end(); ++p) {
            if (p->id == id)
                found = true;
        }
        if (!found) {
            iter1 = shape_neurons.erase(iter1);
            iter2 = neuron_ids.erase(iter2);
        }
        else {
            ++iter1, ++iter2;
        }
    }
    // check neurons (model add)
    for (auto p = this->FNN->_neurons.begin();
         p != this->FNN->_neurons.end(); ++p) {
        int id = p->id;
        bool found = false;
        for (auto iter = neuron_ids.begin();
             iter != neuron_ids.end(); ++iter) {
            if (id == *iter)
                found = true;
            if (!found && *iter > id) { // no this id
                neuron_ids.insert(iter, id);
                found = true;
                break;
            }
        }
        if (!found)
            neuron_ids.append(id);  // if no place to insert, then append
    }
}
void NetView::check_FNN_weights()
{
    // check weights delete
    auto iter1 = topology_weights.begin();
    auto iter2 = weight_ids.begin();
    while (iter1 != topology_weights.end()) {
        int id = *iter2;
        bool found = false;
        for (auto p = this->FNN->_weights.begin();
             p != this->FNN->_weights.end(); ++p) {
            if (p->id == id)
                found = true;
        }
        if (!found) {
            iter1 = topology_weights.erase(iter1);
            iter2 = weight_ids.erase(iter2);
        }
        else {
            ++iter1, ++iter2;
        }
    }
    // check weights (model add)
    for (auto p = this->FNN->_weights.begin();
         p != this->FNN->_weights.end(); ++p) {
        int id = p->id;
        bool found = false;
        for (auto iter = weight_ids.begin();
             iter != weight_ids.end(); ++iter) {
            if (id == *iter)
                found = true;
            if (!found && *iter > id) { // no this id
                weight_ids.insert(iter, id);
                found = true;
                break;
            }
        }
        if (!found)
            weight_ids.append(id);  // if no place to insert, then append
    }
}
void NetView::check_FNN()
{
    check_FNN_neurons();
    check_FNN_weights();
}

void NetView::paintNeurons(QPainter *painter)
{
    if (edit_mode == addNeuron) {
        switch (current_neuron.type) {
        case nNone:
            painter->setPen(QPen(Qt::black, 1));
            break;
        case nSigmoid:
            painter->setPen(QPen(Qt::darkRed, 1));
            break;
        case nRelu:
            painter->setPen(QPen(Qt::darkGreen, 1));
            break;
        case nTanh:
            painter->setPen(QPen(Qt::darkBlue, 1));
            break;
        case nTarget:
            painter->setPen(QPen(Qt::black, 1));
            break;
        default:
            painter->setPen(QPen(Qt::black, 1));
            break;
        }
        painter->drawEllipse(shape_current_neuron);
    }

    QColor n_color;
    for (int i = 0; i != shape_neurons.size(); ++i) {
        switch (this->FNN->_neurons.at(i).type)
        {
        case nSigmoid:
            n_color = Qt::darkRed;
            break;
        case nRelu:
            n_color = Qt::darkGreen;
            break;
        case nTanh:
            n_color = Qt::darkBlue;
            break;
        case nTarget:
            n_color = Qt::black;
            break;
        default:
            n_color = Qt::black;
            break;
        }
        painter->setPen(QPen(n_color, 2));
        switch (this->FNN->_neurons.at(i).isleaf) {
        case nInput:
            painter->setBrush(QBrush(n_color, Qt::NoBrush));
            break;
        case nHidden:
            painter->setBrush(QBrush(n_color, Qt::Dense7Pattern));
            break;
        case nOutput:
            painter->setBrush(QBrush(n_color, Qt::Dense7Pattern));
            break;
        default:
            break;
        }
        painter->drawEllipse(shape_neurons.at(i));


        if (this->FNN->_neurons.at(i).type == nTarget) {
            QRectF outer = shape_neurons.at(i);
            outer.setTopLeft(QPointF(outer.left() - 3, outer.top() - 3));
            outer.setBottomRight(QPointF(outer.right() + 3, outer.bottom() + 3));
            painter->drawEllipse(outer);
            QString disptext =
                    QString::number(this->FNN->_neurons.at(i)._targetvalue, 10, 2)
                    + "\n"
                    + QString::number(this->FNN->_neurons.at(i)._value, 10, 2);
            painter->drawText(newQRectF(
                                 shape_neurons.at(i).center(),
                                 24),
                             Qt::AlignCenter,
                             disptext);
        }
        else {
            painter->drawText(newQRectF(
                                 shape_neurons.at(i).center(),
                                 20),
                             Qt::AlignCenter,
                             QString::number(
                                 this->FNN->_neurons.at(i)._value,
                                 10, 2));
        }
        if (selected_neuron == this->FNN->_neurons.at(i).id) {
            QRectF outer = shape_neurons.at(i);
            outer.setTopLeft(QPointF(outer.left() - 4, outer.top() - 4));
            outer.setBottomRight(QPointF(outer.right() + 4, outer.bottom() + 4));
            painter->drawRect(outer);
        }
    }
}
void NetView::paintWeights(QPainter *painter)
{
    shape_weights.clear();
    for (int i = 0; i != topology_weights.size(); ++i) {

        painter->setPen(QPen(Qt::black, 1));
        if (FNN->_weights.at(i).id == selected_weight)
            painter->setPen(QPen(Qt::black, 2));
        QPointF p1, p2;
        for (int j = 0; j != this->FNN->_neurons.size(); ++j) {
            if (this->FNN->_neurons.at(j).id == topology_weights.at(i).first)
                p1 = shape_neurons.at(j).center();
            if (this->FNN->_neurons.at(j).id == topology_weights.at(i).second)
                p2 = shape_neurons.at(j).center();
        }
        QPointF dp;
        dp.setX(p2.x() - p1.x());
        dp.setY(p2.y() - p1.y());
        double l = sqrt(dp.x() * dp.x() + dp.y() * dp.y());
        p1.setX(p1.x() + dp.x() * _radius / l);
        p1.setY(p1.y() + dp.y() * _radius / l);
        p2.setX(p2.x() - dp.x() * _radius / l);
        p2.setY(p2.y() - dp.y() * _radius / l);
        shape_weights.append(QLineF(p1, p2));
        painter->drawLine(QLineF(p1, p2));
        painter->drawRect(newQRectF(p1, 4));    // from
        painter->drawEllipse(newQRectF(p2, 3)); // to

        // display weight and gradient
        QPointF midp = (p1 + p2) / 2;
        if (l > 4 * _radius)
            painter->drawText(newQRectF(midp, 48),
                              Qt::AlignCenter,
                              QString::number(this->FNN->_weights.at(i)._weight, 10, 2)
                              + QString("/")
                              + QString::number(this->FNN->_weights.at(i)._gradient, 10, 2));
    }
    if (drag_mode == lineDrag) {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawLine(shape_current_weight);
    }
}
