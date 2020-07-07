#include "app.h"

App::App(): view(new View), model(new Model), viewmodel(new ViewModel)
{
	viewmodel->bind(model);
	
	view->set_neurons(viewmodel->get_neurons());
	view->set_weights(viewmodel->get_weights());

	view->set_select_command(viewmodel->get_select_command());
	view->set_add_none_command(viewmodel->get_add_none_command());
	view->set_add_sigmoid_command(viewmodel->get_add_sigmoid_command());
	view->set_add_relu_command(viewmodel->get_add_relu_command());
	view->set_add_tanh_command(viewmodel->get_add_tanh_command());
	view->set_drag_command(viewmodel->get_drag_command);
	view->set_connect_command(viewmodel->get_connect_command);

	viewmodel->set_update_view_notification(view->get_update_view_notification);

	model->set_update_display_data_notification(viewmodel->get_update_display_data_notification);
}