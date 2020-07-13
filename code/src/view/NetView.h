#pragma once

#ifndef NETVIEW_H
#define NETVIEW_H

#include <memory>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QVector>
#include <QPair>
#include <QGraphicsItem>
#include "../viewmodel/NetViewModel.h"
#include "../common/Common.h"
#include "NeuronView.h"
#include "WeightView.h"
#include "ConfigView.h"

enum EditMode {
	selectNeuron, addNeuron, addWeight
};
enum DragMode {
    noDrag, preDrag, canDrag, isDrag, lineDrag
};

QT_BEGIN_NAMESPACE
namespace Ui { class NetView; }
QT_END_NAMESPACE


class NetView : public QMainWindow {
	Q_OBJECT 
public:
    explicit NetView(QWidget* parent = nullptr);
    ~NetView();
	

    //BIND COMMANDS
    void set_add_neuron_command(Command&&);
    void set_connect_command(Command&&);    // commit: addweights
    void set_change_neuron_command(Command&&);  // commit: addvalue
    void set_change_weight_command(Command&&);  // commit: addvalue

    void set_calculate_forward_command(Command&&);  // commit: addcalcforward
    void set_calculate_gradient_command(Command&&);
    void set_propagate_gradient_command(Command&&);
    void set_update_weights_command(Command&&);
    void set_backprop_command(Command&&);

    void set_delete_weight_command(Command&&);
    void set_delete_neuron_command(Command&&);

    void set_change_learning_rate_command(Command&&);
    void set_change_loss_command(Command&&);
    void set_demand_config_command(Command&&);

	//ATTACH DATA AND MODELS
    void set_FNN(std::shared_ptr<Graph>);
	void attach_ViewModel(std::shared_ptr<NetViewModel> refModel) noexcept;
	std::shared_ptr <NetViewModel > detach_ViewModel() noexcept;

	//retrun NOTIFICATION(IMPLEMENTED BY VIEW)
	Notification tell_update_view_notification();
    Notification tell_property_change_notification();

private slots:
	void select_button_clicked();
	void neuron_button_clicked();
	void sigmoid_button_clicked();
	void relu_button_clicked();
	void tanh_button_clicked();
	void target_button_clicked();

    void calc_forward_clicked();    // commit: addcalcforward
    void calc_gradient_clicked();
    void prop_gradient_clicked();
    void update_weights_clicked();
    void backprop_clicked();
    void delete_button_clicked();

    void change_neuron_value(QPair<QPair<int, double>, NeuronType>);
    void change_weight_value(QPair<int, double>);
    void change_learning_rate(double);
    void change_loss(QString);
    void enter_config();
    void change_config(QPair<double, QString>);

    void exit_clicked();
    void iterate_clicked();


private:
	/*Ui::View *ui;*/
	//MODELS AND DATA BIND
	std::shared_ptr<Graph> FNN;
	std::shared_ptr<NetViewModel> m_NetVM;

    //COMMANDS
    Command add_neuron_command;
    Command connect_command;    // commit: addweights
    Command change_neuron_command;  // commit: addvalue
    Command change_weight_command;  // commit: addvalue

    Command calculate_forward_command;  // commit: addcalcforward
    Command calculate_gradient_command;
    Command propagate_gradient_command;
    Command update_weights_command;
    Command backprop_command;

    Command delete_weight_command;
    Command delete_neuron_command;

    Command change_learning_rate_command;
    Command change_loss_command;

    Command demand_config_command;

	// edit state
	EditMode edit_mode;
    DragMode drag_mode;
    Neuron current_neuron;
//    QVector<bool> selected_neurons;
    int selected_neuron;
    int selected_weight;

	// shape of the Graph
    QVector<QRectF> shape_neurons;
    QVector<int> neuron_ids;
    QRectF shape_current_neuron;

    QVector<QPair<int, int> > topology_weights;
    QVector<QLineF> shape_weights;
    QVector<int> weight_ids;
    QLineF shape_current_weight;

    // display modules
    Ui::NetView *ui;
    NeuronView *neuronView;
    WeightView *weightView;
    ConfigView *configView;

    // internal functions;
    void paintNeurons(QPainter*);
    void paintWeights(QPainter*);
    void check_FNN();
    void check_FNN_neurons();
    void check_FNN_weights();

protected:
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent*);
	void paintEvent(QPaintEvent*);

};


#endif // !VIEW_H
