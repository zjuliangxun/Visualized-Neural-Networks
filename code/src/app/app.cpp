#include "app.h"

App::App()
{
	viewmodel.attach_Model(std::shared_ptr<NetModel>(&this->model));//bind model
	view.attach_ViewModel(std::shared_ptr<NetViewModel>(&this->viewmodel));

	//bind view
    view.set_FNN(viewmodel.get_FNN());

    view.set_add_neuron_command(viewmodel.get_add_neuron_command());
//	view.set_connect_command(viewmodel.get_connect_command());

	// viewmodel
	viewmodel.AddNotification(view.tell_update_view_notification());//add notification

	//model
	model.AddNotification(viewmodel.get_Notification());//add notification
	//!!!!!!!!need to transfer to left value
}

void App::run() {
	view.show();
}
