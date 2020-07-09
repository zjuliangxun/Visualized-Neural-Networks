#include "NetModel.h"

std::function<bool(Neuron&&)> NetModel::get_add_neuron_command() {
    return [this](Neuron&& x)->bool {
        return this->add_neuron(std::move(x));
    };
}

std::shared_ptr<Graph> NetModel::get_FNN()
{
    return std::shared_ptr<Graph>(&(this->FNN));
}

void NetModel::set_update_display_data_notification(Notification&& notification)
{
    AddNotification(std::move(notification));
}


bool NetModel::add_neuron(Neuron&& x)
{
    return this->FNN.add_neuron(std::move(x));
}
