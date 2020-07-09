#include "NetView.h"
#include "ui_NetView.h"
#include <QPair>

/* auxiliary functions */
static int _radius = 16;
QRect newQRect(QPoint, int);
bool conflict(const QRect &lhs, const QRect &rhs);

/* View Definition */
NetView::NetView(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::NetView)
{
    ui->setupUi(this);
    resize(800, 600);
    setWindowTitle("Visualized Neural Networks");

    setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->resize(800, 600);
    ui->graphicsView->hide();

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
    addNeuronTargetAction->setIcon(QIcon(":/images/neuron_Target.png"));
    tbar->addAction(addNeuronTargetAction);


    // signal-slots connection
    connect(selectAction, SIGNAL(triggered()), this, SLOT(select_button_clicked()));
    connect(addNeuronNoneAction, SIGNAL(triggered()), this, SLOT(neuron_button_clicked()));
    connect(addNeuronSigmoidAction, SIGNAL(triggered()), this, SLOT(sigmoid_button_clicked()));
    connect(addNeuronReluAction, SIGNAL(triggered()), this, SLOT(relu_button_clicked()));
    connect(addNeuronTanhAction, SIGNAL(triggered()), this, SLOT(tanh_button_clicked()));
    connect(addNeuronTargetAction, SIGNAL(triggered()), this, SLOT(target_button_clicked()));

    // initialize internal states
    selected_neuron = -1;
    edit_mode = selectNeuron;
    drag_mode = noDrag;
}

NetView::~NetView()
{
    delete ui;
}


void NetView::set_FNN(std::shared_ptr<Graph> pFNN)
{
    this->FNN = pFNN;
}
void NetView::attach_ViewModel(std::shared_ptr <NetViewModel > refModel) noexcept {
	this->m_NetVM = refModel;
}
std::shared_ptr <NetViewModel > NetView::detach_ViewModel() noexcept {
	return std::shared_ptr <NetViewModel >(std::move(m_NetVM));
}

void NetView::paintEvent(QPaintEvent*)
{
    QPixmap map(size());
    map.fill(Qt::white);
    QPainter painter(&map);

    for (int i = 0; i != shape_neurons.size(); ++i) {
        switch (this->FNN->_neurons.at(i).type)
        {
        case nSigmoid:
            if (edit_mode == addNeuron) {
                painter.setPen(QPen(Qt::darkRed, 1));
                painter.drawEllipse(shape_current_neuron);
            }
            painter.setPen(QPen(Qt::darkRed, 2));
            break;
        case nRelu:
            if (edit_mode == addNeuron) {
                painter.setPen(QPen(Qt::darkGreen, 1));
                painter.drawEllipse(shape_current_neuron);
            }
            painter.setPen(QPen(Qt::darkGreen, 2));
            break;
        case nTanh:
            if (edit_mode == addNeuron) {
                painter.setPen(QPen(Qt::darkBlue, 1));
                painter.drawEllipse(shape_current_neuron);
            }
            painter.setPen(QPen(Qt::darkBlue, 2));
            break;
        case nTarget:
            if (edit_mode == addNeuron) {
                painter.setPen(QPen(Qt::black, 1));
                painter.drawEllipse(shape_current_neuron);
            }
            painter.setPen(QPen(Qt::black, 2));
            break;
        default:
            if (edit_mode == addNeuron) {
                painter.setPen(QPen(Qt::black, 1));
                painter.drawEllipse(shape_current_neuron);
            }
            painter.setPen(QPen(Qt::black, 2));
            break;
        }
        painter.drawEllipse(shape_neurons.at(i));
        if (this->FNN->_neurons.at(i).type == nTarget) {
            QRect outer = shape_neurons.at(i);
            outer.setTopLeft(QPoint(outer.left() - 3, outer.top() - 3));
            outer.setBottomRight(QPoint(outer.right() + 3, outer.bottom() + 3));
            painter.drawEllipse(outer);
        }
        if (selected_neurons.at(i)) {
            QRect outer = shape_neurons.at(i);
            outer.setTopLeft(QPoint(outer.left() - 4, outer.top() - 4));
            outer.setBottomRight(QPoint(outer.right() + 4, outer.bottom() + 4));
            painter.drawRect(outer);
        }
    }

    painter.end();
    painter.begin(this);
    painter.drawPixmap(0, 0, map);
}
void NetView::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        if (edit_mode == selectNeuron) {
            bool select_one = false;
            for (int i = 0; i != this->FNN->_neurons.size(); ++i) {
                QPoint old_c = shape_neurons.at(i).center();
                QPoint new_c(e->pos());
                int dx = old_c.x() - new_c.x();
                int dy = old_c.y() - new_c.y();
                if (dx * dx + dy * dy <= _radius * _radius) {
                    selected_neurons.replace(i, true);
                    if (selected_neuron == i)
                        drag_mode = canDrag;
                    else
                        selected_neuron = i;
                    select_one = true;
                }
                else
                    selected_neurons.replace(i, false);
            }
            if (select_one) {

            }
            else {
                drag_mode = noDrag;
                selected_neuron = -1;
            }
        }
    }

    update();
}
void NetView::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        if (edit_mode == selectNeuron) {
            for (int i = 0; i != this->FNN->_neurons.size(); ++i) {
                if (selected_neurons.at(i) && i == selected_neuron)
                    drag_mode = preDrag;
            }
        }
        else if (edit_mode == addNeuron) {
            Neuron x;
            QRect shape_x;
            x.isleaf = 1;
            x.type = current_neuron.type;
            x._value = 0.0;
            int flag = true;
            for (int i = 0; i != this->FNN->_neurons.size() && flag; ++i) {
                QPoint old_c = shape_neurons.at(i).center();
                QPoint new_c(e->pos());
                int dx = old_c.x() - new_c.x();
                int dy = old_c.y() - new_c.y();
                if (dx * dx + dy * dy <= 4 * _radius * _radius)
                    flag = false;
            }
            if (flag) {
                shape_x = newQRect(e->pos(), _radius);
            }

            bool add_success = add_neuron_command(x);  // with return falue
            if (add_success) {
                selected_neurons.append(false);
                shape_neurons.append(shape_x);
            }
        }
    }
    update();
}
//void NetView::mouseDoubleClickEvent(QMouseEvent* e)
//{

//}
void NetView::mouseMoveEvent(QMouseEvent* e)
{
    shape_current_neuron = newQRect(e->pos(), _radius);

    if (drag_mode == canDrag) {
        shape_current_neuron.moveCenter(e->pos());
        int no_conflict = true;
        for (int i = 0; i != shape_neurons.size() && no_conflict; ++i) {
            if (i != selected_neuron &&
                conflict(shape_current_neuron, shape_neurons.at(i)))
                no_conflict = false;
        }
        if (no_conflict) {
            shape_neurons.replace(selected_neuron, shape_current_neuron);
        }
    }

    update();
}

void NetView::set_add_neuron_command(Command&& cmd) {
    this->add_neuron_command = cmd;
}

Notification NetView::tell_update_view_notification() {
	return [this](uint32_t) {
        update();
	};
}

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
    if (selected_neuron != -1)
        selected_neurons.replace(selected_neuron, false);
    selected_neuron = -1;
    update();
}
void NetView::sigmoid_button_clicked()
{
    current_neuron.type = nSigmoid;
    edit_mode = addNeuron;
    if (selected_neuron != -1)
        selected_neurons.replace(selected_neuron, false);
    selected_neuron = -1;
    update();
}
void NetView::relu_button_clicked()
{
    current_neuron.type = nRelu;
    edit_mode = addNeuron;
    if (selected_neuron != -1)
        selected_neurons.replace(selected_neuron, false);
    selected_neuron = -1;
    update();
}
void NetView::tanh_button_clicked()
{
    current_neuron.type = nTanh;
    edit_mode = addNeuron;
    if (selected_neuron != -1)
        selected_neurons.replace(selected_neuron, false);
    selected_neuron = -1;
    update();
}
void NetView::target_button_clicked()
{
    current_neuron.type = nTarget;
    edit_mode = addNeuron;
    if (selected_neuron != -1)
        selected_neurons.replace(selected_neuron, false);
    selected_neuron = -1;
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
bool conflict(const QRect &lhs, const QRect &rhs)
{
    QPoint center = lhs.center();
    QPoint new_center = rhs.center();
    int dx = new_center.x() - center.x();
    int dy = new_center.y() - center.y();
    return (dx * dx + dy * dy <= 4 * _radius * _radius);
}
