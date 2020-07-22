#include "NetViewModel.h"
#include <QString>

NetViewModel::NetViewModel(): m_NetM(nullptr) {}

Command NetViewModel::get_add_neuron_command() {
    return [this](std::any&& x)->bool {
        Neuron&& y = std::any_cast<Neuron>(x);
        return this->m_NetM->add_neuron(std::move(y));
    };
}

Notification  NetViewModel::get_Notification() 
	{
		return [this](uint32_t uID)
		{
            switch (uID) {
            case NOTIF_DRAW:
                this->Fire(uID);
                break;
            case NOTIF_CHANGE:
                this->Fire(uID);
                break;
            default:
                break;
            }
		};
	}

//EXPOSE ATTRIBUTES
std::shared_ptr<Graph> NetViewModel::get_FNN()
{
    return (this->m_NetM->get_FNN());
}

//ATTACH  MODEL
void NetViewModel::attach_Model(std::shared_ptr<NetModel> refModel) noexcept
{
    this->m_NetM = refModel;
}
std::shared_ptr<NetModel> NetViewModel::detach_Model() noexcept
{
    std::shared_ptr<NetModel> tmp_ptr = this->m_NetM;
    this->m_NetM = nullptr;
    return tmp_ptr;
}

Command NetViewModel::get_connect_command(){
    return [this](std::any t)->bool{
        QPair<int,int> g=std::any_cast<QPair<int,int>>(t);
        return this->m_NetM->add_link(g.first,g.second);
    };
}

Command NetViewModel::get_change_neuron_command(){
    return [this](std::any t)->bool{
        QPair<QPair<int, double>, NeuronType> g
                = std::any_cast<QPair<QPair<int, double>, NeuronType> >(t);
        QPair<int, double> value(g.first);
        NeuronType tp(g.second);
        bool success = (tp != nTarget);
        success &= this->m_NetM->change_neruo(value.first,value.second);
        success &= this->m_NetM->change_neruo_type(value.first, tp);
        return success;
    };
}

Command NetViewModel::get_change_weight_command(){
    return [this](std::any t)->bool{
        QPair<int,double> g=std::any_cast<QPair<int,double>>(t);
        return this->m_NetM->change_weight(g.first,g.second);
    };
}

Command NetViewModel::get_calculate_forward_command(){
    return [this](std::any t)->bool{
        return this->m_NetM->calculate_forward();
    };
}

Command NetViewModel::get_calculate_gradient_command(){
    return [this](std::any t)->bool{
        return this->m_NetM->calculate_gradient();
    };
}

Command NetViewModel::get_propagate_gradient_command(){
    return [this](std::any t)->bool{
        return this->m_NetM->propagate_gradient();
    };
}
Command NetViewModel::get_update_weights_command(){
    return [this](std::any t)->bool{
        return this->m_NetM->update_weights();
    };
}
Command NetViewModel::get_backprop_command(){
    return [this](std::any t)->bool{
        int *p = std::any_cast<int*>(t);
        return this->m_NetM->backprop(p);
    };
}

Command NetViewModel::get_delete_weight_command(){
    return [this](std::any t)->bool{
        int g=std::any_cast<int>(t);
        return this->m_NetM->delete_weight(g);
    };
}

Command NetViewModel::get_delete_neuron_command(){
    return [this](std::any t)->bool{
        int g=std::any_cast<int>(t);
        return this->m_NetM->delete_neuron(g);
    };
}

Command NetViewModel::get_demand_config_command(){
    return [this](std::any t)->bool{
        QPair<double,QString>* g=std::any_cast<QPair<double,QString>*>(t);
        g->first=this->m_NetM->get_learning_rate();
        g->second=this->m_NetM->get_loss_func();
        return true;
    };
}

Command NetViewModel::get_change_learning_rate_command() {
    return [this](std::any t)->bool {
        double x = std::any_cast<double>(t);
        return this->m_NetM->change_learning_rate(x);
    };
}

Command NetViewModel::get_change_loss_command() {
    return [this](std::any t)->bool {
        QString s = std::any_cast<QString>(t);
        LossFunc f = lossL2;
        if (s == "L1")
            f = lossL1;
        if (s == "L2")
            f = lossL2;
        return this->m_NetM->change_loss(f);
    };
}
