#include "app.h"

App::App()
{
    model=make_shared<NetModel>();
    viewmodel=make_shared<NetViewModel>();
    view =make_shared<NetView >();

    viewmodel->attach_Model(this->model);//bind model
    view->attach_ViewModel(this->viewmodel);

	//bind view
    view->set_FNN(viewmodel->get_FNN());

    view->set_add_neuron_command(viewmodel->get_add_neuron_command());
    view->set_connect_command(viewmodel->get_connect_command());
    view->set_change_neuron_command(viewmodel->get_change_neuron_command());
    view->set_change_weight_command(viewmodel->get_change_weight_command());
    view->set_calculate_forward_command(viewmodel->get_calculate_forward_command());
    view->set_calculate_gradient_command(viewmodel->get_calculate_gradient_command());
    view->set_propagate_gradient_command(viewmodel->get_propagate_gradient_command());
    view->set_update_weights_command(viewmodel->get_update_weights_command());
    view->set_backprop_command(viewmodel->get_backprop_command());
    view->set_delete_weight_command(viewmodel->get_delete_weight_command());

	// viewmodel
    viewmodel->AddNotification(view->tell_update_view_notification());//add notification
    viewmodel->AddNotification(view->tell_update_view_notification());//add notification

	//model
    model->AddNotification(viewmodel->get_Notification());//add notification
	//!!!!!!!!need to transfer to left value
}

void App::run() {
    view->show();
}

App::~App(){
    //view.reset();
    model.reset();
    viewmodel.reset();


}
