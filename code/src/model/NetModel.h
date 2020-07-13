#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <QtCore/QVector>
#include "../common/Common.h"
#include "../common/Graph.h"
#include "math_utils.h"

class NetModel :public PropertyTrigger{
private:
    //QVector<Neuron> neurons;
    //QVector<Weight> weights;
    shared_ptr<Graph> FNN;
    LossFunc loss_func;     // maybe changed in the future
    double learning_rate;   // learning rate
public:
    NetModel();
    //expose
    std::shared_ptr<Graph> get_FNN();

    //get notifications-----through AddNotifications
    void set_update_display_data_notification(Notification&& notification);

    //commands' core
    bool add_neuron(Neuron&&);
    bool add_link(int src,int dst);
    bool change_neruo(int id, double value);
    bool change_neruo_type(int id, NeuronType tp);
    bool change_weight(int id, double value);
    //estimate whether there exist circle
    bool estimate_circle(int src, int dst);
    bool calculate_forward();
    bool calculate_gradient();
    bool propagate_gradient();
    bool update_weights();   // according to learning_rate
    bool backprop(int*);    // combine gradient calculate&update weight
    bool delete_weight(int id);
    bool delete_neuron(int id);
//	void move(int);
    bool change_learning_rate(double);
    bool change_loss(LossFunc);

    double get_learning_rate();
    QString get_loss_func();
};

#endif // !MODEL_H
