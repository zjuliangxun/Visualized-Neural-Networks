#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QtWidgets>
#include <memory>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QVector>
#include "../app/notification.h"
#include "../app/command.h"
#include "../common/weights.h"
#include "../common/neurons.h"

class ViewModel {
private:
	std::shared_ptr<QVector<Neuron> > neurons;
	std::shared_ptr<QVector<Weight> > weights;
	std::shared_ptr<Command> select_command;
	std::shared_ptr<Command> add_none_command;
	std::shared_ptr<Command> add_sigmoid_command;
	std::shared_ptr<Command> add_relu_command;
	std::shared_ptr<Command> add_tanh_command;
	std::shared_ptr<Command> drag_command;
	std::shared_ptr<Command> connect_command;

	std::shared_ptr<Notification> update_view_notification;
	std::shared_ptr<Notification> update_display_data_notification;

public:
	ViewModel();

	void bind(std::shared_ptr<Model> model);

	void exc_select_command();
	void exc_add_none_command();
	void exc_add_sigmoid_command();
	void exc_add_relu_command();
	void exc_add_tanh_command();
	void exc_drag_command();
	void exc_connect_command();

	void set_update_view_notification(std::shared_ptr<Notification> notification);

	std::shared_ptr<Command> get_select_command();
	std::shared_ptr<Command> get_add_none_command();
	std::shared_ptr<Command> get_add_sigmoid_command();
	std::shared_ptr<Command> get_add_relu_command();
	std::shared_ptr<Command> get_add_tanh_command();
	std::shared_ptr<Command> get_drag_command();
	std::shared_ptr<Command> get_connect_command();

	std::shared_ptr<Notification> get_update_display_data_notification;
	
	std::shared_ptr<QVector<Neuron> > get_neurons();
	std::shared_ptr<QVector<Neuron> > get_weights();

	void notified();
};

#endif // !VIEWMODEL_H
